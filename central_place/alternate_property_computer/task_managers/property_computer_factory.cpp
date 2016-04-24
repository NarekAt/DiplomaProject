#include "property_computer_factory.h"
#include "property_computers.h"

namespace Base
{

//////////////////// PropertyComputerController ////////////////////

void
PropertyComputerController::registerPropertyComputers()
{
    mm.insert(std::make_pair(CONNECTED_COMPONENTS, make_holder<ConnectedComponents>));
    mm.insert(std::make_pair(SHORTEST_PATH, make_holder<ShortestPath>));
    mm.insert(std::make_pair(BETWEENNESS_CENTRALITY, make_holder<BC>));
    mm.insert(std::make_pair(EIGENVECTOR_CENTRALITY, make_holder<EVC>));
    mm.insert(std::make_pair(EIGEN_VALUES, make_holder<EigenValues>));
    mm.insert(std::make_pair(DEGREE, make_holder<DegreeComputer>));
}

std::unique_ptr<Holder>
PropertyComputerController::createPropertyComputer(alternate_property_type const E, graph_types::graph& g)
{
    auto it = mm.find(E);

    if (it == mm.end())
    {
        return std::unique_ptr<Holder>();
    }

    return (*it->second)(g);
}

////////////////////// PropertyComputerRunner /////////////////////////

void
PropertyComputerRunner::compute_and_write(graph_types::graph& g, alternate_property_type const p, bool calcDistr)
{
    auto& ctrl = PropertyComputerController::getInstance();
    std::unique_ptr<Holder> holder = ctrl.createPropertyComputer(p, g);
    if (not holder)
    {
        std::cerr << "Unknown type " << (int)p << "\n";
        return;
    }

    holder->compute();
    holder->writeResults();

    if (calcDistr)
        holder->writeDistribution();
}

}
