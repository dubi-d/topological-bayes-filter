#include "topological_bayes_filter/topological_bayes_filter.hpp"

namespace topological_bayes_filter{

class TbfExample : public TopoBayesFilter {

  using TopoBayesFilter::TopoBayesFilter;  // inherit base constructor

public:
    void setMeasurement(int measurement) {
      measurement_ = measurement;
    };

private:
    void sense() override {
      std::cout << "sense()" << std::endl;
      for(int i = 0; i < numVertices_; ++i) {
        if (i == measurement_) {
          posterior_(i) = 0.8;
        }
        else {
          posterior_(i) = 0.1;
        }
      }
      std::cout << "measurement model: " << posterior_ << std::endl;
    };

    int measurement_;
};
}

int main() {
  int numVertices = 5;
  double transitionProbability = 0.5;
  bool verbose = true;
  topological_bayes_filter::TbfExample tbf(numVertices, transitionProbability, verbose);

  for (int i=1; i<4; ++i) {
    tbf.addEdge(i, i+1);
    tbf.addEdge(i, i-1);
  }
  tbf.addEdge(0, 1);
  tbf.addEdge(4, 3);
  tbf.addEdge(1, 4);
  tbf.removeDuplicateEdges();
  tbf.printGraph();

  int estimate;
  tbf.setMeasurement(0);
  tbf.update();
  tbf.getEstimate();
  tbf.setMeasurement(2);
  tbf.update();
  tbf.getEstimate();
  return 0;
}