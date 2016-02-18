#include "degree_computer.h"
#include "parallel_for.h"


namespace Base
{

void
DegreeComputer::computeImpl()
{
    graph_types::graph_size size = graph_.size();

    MT::parallel_for(0, size - 1, [&](unsigned index){
            results_[index] = graph_.degree(index); });
}

alternate_property_type
DegreeComputer::typeImpl() const
{
    return DEGREE;
}

DegreeComputer::ResultType
DegreeComputer::getDistributionImpl() const
{
    ResultType distributions (results_.size(), 0u);

    for (const auto& r : results_)
    {
        distributions[r]++;
    }
    return distributions;
}

} // namespace Base
