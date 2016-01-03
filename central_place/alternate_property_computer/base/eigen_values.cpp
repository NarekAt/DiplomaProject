#include "eigen_values.h"

// Eigen library
#include <Eigen/Eigenvalues>

using Eigen::MatrixXd;
using Eigen::VectorXcd;

namespace
{

void fillUpAdjacencyMatrix(const graph_types::graph& g, MatrixXd& m)
{
    const graph_types::graph_size size = g.size();

    for (unsigned vX = 0; vX != size; ++vX)
    {
        for(unsigned vY = 0; vY != size; ++vY)
        {
            if (g.edge_exists(vX, vY))
                    m(vX, vY) = 1;
        }
    }
}

} // anonymous namespace

namespace Base
{

void
EigenValues::computeImpl()
{
    MatrixXd matrix = MatrixXd::Zero(graph_.size(), graph_.size());
    fillUpAdjacencyMatrix(graph_, matrix);

    VectorXcd eivals = matrix.eigenvalues();

    results_.clear();
    results_.reserve(eivals.size());

    for(unsigned i = 0; i != eivals.size(); ++i)
    {
        results_.push_back(eivals[i]);
    }
}

PropertyComputerType
EigenValues::typeImpl() const
{
    return EIGEN_VALUES;
}

EigenValues::ResultType
EigenValues::getDistributionImpl() const
{
    throw std::logic_error("Property distribution is meaningless for EigenValues");
    return ResultType();
}

} // namespace Base
