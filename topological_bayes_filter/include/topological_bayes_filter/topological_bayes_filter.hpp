#include <vector>
#include <iostream>

#include <Eigen/Core>

namespace topological_bayes_filter{

class TopoBayesFilter {

public:
    TopoBayesFilter(std::size_t numVertices, double transitionProbability,
                    const bool verbose=false);  //! Constructor 1
    TopoBayesFilter() {};  //! Constructor 2 (empty)
    virtual ~TopoBayesFilter() {}; //! Destructor

    virtual void addEdge(int i, int j);
    virtual void removeDuplicateEdges();
    virtual void reset();
    virtual void update();
    virtual int getEstimate();
    virtual void printVertex(int i);
    virtual void printGraph();

protected:
    virtual void propagate();
    virtual void sense() = 0;  // Implement your measurement model. Use posterior_ to store the result.
    virtual void updatePosterior();

    std::size_t numVertices_;
    double transitionProbability_;
    bool verbose_ = false;

    std::vector<std::vector<int>> adjacencyList_;
    Eigen::VectorXd prior_;
    Eigen::VectorXd posterior_;
};

}  // end of namespace topological_bayes_filter