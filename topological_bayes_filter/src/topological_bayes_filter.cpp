#include "topological_bayes_filter/topological_bayes_filter.hpp"

namespace topological_bayes_filter{

TopoBayesFilter::TopoBayesFilter(size_t numVertices)
: numVertices_(numVertices)
{
  adjacencyList_.resize(numVertices_);
  prior_.resize(numVertices_, 1.0/numVertices_);
  posterior_.resize(numVertices_, 0.0);
}

void TopoBayesFilter::addEdge(int i, int j) {
  /*
   * Add an edge from vertex i to vertex j
   * */
  adjacencyList_[i].push_back(j);
}

void TopoBayesFilter::reset() {

}

void TopoBayesFilter::update() {

}

int TopoBayesFilter::getEstimate() {

}

void TopoBayesFilter::propagate() {

}

void TopoBayesFilter::sense() {

}

void TopoBayesFilter::updatePosterior() {

}

}  // end of namespace topological_bayes_filter