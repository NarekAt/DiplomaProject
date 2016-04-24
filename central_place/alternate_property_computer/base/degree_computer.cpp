#include "degree_computer.h"
#include "parallel_for.h"


namespace Base
{

void
DegreeComputer::computeImpl()
{
    graph_types::graph_size size = graph_.size();

    for (unsigned index = 0; index != size; ++index)
    {
        std::cout << graph_.degree(index) << std::endl;
        results_[index] = graph_.degree(index);
    }
    //MT::parallel_for(0, size - 1, [&](unsigned index){
    //        results_[index] = graph_.degree(index); });
}

alternate_property_type
DegreeComputer::typeImpl() const
{
    return DEGREE;
}

DegreeComputer::ResultType
DegreeComputer::getDistributionImpl() const
{
    ResultType distributions;

    for (const auto& r : results_)
    {
        if (r >= distributions.size())
            distributions.resize(r + 1);

        ++(distributions[r]);
    }
    return distributions;
}

} // namespace Base
