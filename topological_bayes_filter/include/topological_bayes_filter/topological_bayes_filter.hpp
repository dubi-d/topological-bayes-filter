#include <vector>

#include <Eigen/Core>

namespace topological_bayes_filter{

class TopoBayesFilter {

public:
    TopoBayesFilter(std::size_t numVertices);  //! Constructor
    ~TopoBayesFilter(){}; //! Destructor

    void addEdge(int i, int j);
    void reset();
    void update();
    int getEstimate();


protected:
    void propagate();
    void sense();
    void updatePosterior();

    std::size_t numVertices_;
    std::vector<std::vector<int>> adjacencyList_;
    std::vector<double> prior_;
    std::vector<double> posterior_;
};

}  // end of namespace topological_bayes_filter