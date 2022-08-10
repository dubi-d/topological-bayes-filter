#include "topological_bayes_filter/topological_bayes_filter.hpp"

namespace topological_bayes_filter{

TopoBayesFilter::TopoBayesFilter(size_t numVertices, double transitionProbability)
: numVertices_(numVertices),
  transitionProbability_(transitionProbability)
{
  adjacencyList_.resize(numVertices_);
  prior_.setConstant(numVertices_, 1.0/numVertices_);  // resize & assign values
  posterior_.setConstant(numVertices_, 1.0/numVertices_);
}

void TopoBayesFilter::addEdge(int i, int j) {
  /*
   * Add an edge from vertex i to vertex j
   * */
  adjacencyList_[i].push_back(j);
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
  std::cout << "---- update tbf ----" << std::endl;
  std::cout << "prior: " << prior_ << std::endl;
  this->propagate();
  this->sense();
  this->updatePosterior();
}

int TopoBayesFilter::getEstimate() {
  int index;
  double maxValue = posterior_.maxCoeff(&index);
  std::cout << "Max value: " << maxValue << " at index: " << index << std::endl;
  return index;
}

void TopoBayesFilter::propagate() {
  for(int i = 0; i < numVertices_; ++i) {
    for(auto &neighborVertex : adjacencyList_[i]) {
      prior_(i) += posterior_(neighborVertex) * transitionProbability_;
    }
  }
  std::cout << "propagated prior: " << prior_ << std::endl;
}

void TopoBayesFilter::sense() {
  std::cout << "Override sense() method to use it in your context." << std::endl;
}

void TopoBayesFilter::updatePosterior() {
  posterior_ = posterior_.cwiseProduct(prior_);  // apply measurement update
  posterior_ = posterior_ / posterior_.sum();
  std::cout << "posterior: " << posterior_ << std::endl;
  prior_ = posterior_;
}

}  // end of namespace topological_bayes_filter