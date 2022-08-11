#include "topological_bayes_filter/topological_bayes_filter.hpp"

namespace topological_bayes_filter{

TopoBayesFilter::TopoBayesFilter(size_t numVertices, double transitionProbability, bool verbose)
: numVertices_(numVertices),
  transitionProbability_(transitionProbability),
  verbose_(verbose)
{
  adjacencyList_.resize(numVertices_);
  prior_.setConstant(numVertices_, 1.0/numVertices_);  // resize & assign values
  posterior_.setConstant(numVertices_, 1.0/numVertices_);
}

void TopoBayesFilter::addEdge(int i, int j) {
  /*
   * Add an edge from vertex i to vertex j (undirected edge)
   * */
  adjacencyList_[i].push_back(j);
  adjacencyList_[j].push_back(i);
}

void TopoBayesFilter::removeDuplicateEdges() {
  /*
   * Sort each vertex' adjacency list and remove duplicate entries.
   */
  for ( int i = 0; i < numVertices_; ++i ) {
    std::sort(adjacencyList_[i].begin(), adjacencyList_[i].end());
    auto last = std::unique(adjacencyList_[i].begin(), adjacencyList_[i].end());
    adjacencyList_[i].erase(last, adjacencyList_[i].end());
  }
}

void TopoBayesFilter::reset() {
  /*
   * Reset prior and posterior probabilities.
   */
  prior_.fill(1.0/numVertices_);
  posterior_.fill(1.0/numVertices_);
}

void TopoBayesFilter::update() {
  /*
   * Perform a complete update consisting of propagating the previous posterior,
   * incorporating the measurement and updating the posterior belief.
   */
  if (verbose_) {
    std::cout << "---- update tbf ----" << std::endl;
    std::cout << "prior: " << prior_ << std::endl;
  }

  this->propagate();
  this->sense();
  this->updatePosterior();
}

int TopoBayesFilter::getEstimate() {
  int index;
  double maxValue = posterior_.maxCoeff(&index);
  if (verbose_) {
    std::cout << "Max value: " << maxValue << " at index: " << index << std::endl;
  }
  return index;
}

void TopoBayesFilter::propagate() {
  for ( int i = 0; i < numVertices_; ++i ) {
    for ( auto &neighborVertex : adjacencyList_[i] ) {
      prior_(i) += posterior_(neighborVertex) * transitionProbability_;
    }
  }
  if (verbose_) {
    std::cout << "propagated prior: " << prior_ << std::endl;
  }
}

void TopoBayesFilter::updatePosterior() {
  posterior_ = posterior_.cwiseProduct(prior_);  // apply measurement update
  posterior_ = posterior_ / posterior_.sum();
  prior_ = posterior_;
  if (verbose_) {
    std::cout << "posterior: " << posterior_ << std::endl;
  }
}

void TopoBayesFilter::printVertex(int i) {
  // lambda function to print vector
  auto print_vector = [](std::vector<int> vec)
  {
    for (auto el : vec) {
      std::cout << el << " ";
    }
    std::cout << std::endl;
  };
  std::cout << "Vertex " << i << " has neighbors: ";
  print_vector(adjacencyList_[i]);
}

void TopoBayesFilter::printGraph() {
  auto print_vector = [](std::vector<int> vec)
  {
      for (auto el : vec) {
        std::cout << el << " ";
      }
      std::cout << std::endl;
  };
  std::cout << "----- Graph -----" << std::endl;
  for (int i = 0; i < numVertices_; ++i) {
    std::cout << "Vertex " << i << " has neighbors: ";
    print_vector(adjacencyList_[i]);
  }
}


}  // end of namespace topological_bayes_filter