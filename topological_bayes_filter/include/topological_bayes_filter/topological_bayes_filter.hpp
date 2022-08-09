#include <vector>
#include <iostream>

#include <Eigen/Core>

namespace topological_bayes_filter{

class TopoBayesFilter {

public:
    TopoBayesFilter(std::size_t numVertices, double transitionProbability);  //! Constructor
    ~TopoBayesFilter(){}; //! Destructor

    virtual void addEdge(int i, int j);
    virtual void reset();
    virtual void update();
    virtual int getEstimate();

protected:
    virtual void propagate();
    virtual void sense();
    virtual void updatePosterior();

    std::size_t numVertices_;
    double transitionProbability_;

    std::vector<std::vector<int>> adjacencyList_;
    Eigen::VectorXd prior_;
    Eigen::VectorXd posterior_;
};

}  // end of namespace topological_bayes_filter