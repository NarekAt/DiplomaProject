#include "property_computer_factory.h"
#include "connected_components.h"
#include "shortestpath.h"
#include "betweenness_centrality.h"
#include "degree_computer.h"
#include "eigen_values.h"

#include <assert.h>
#include <functional>

#include <boost/any.hpp>

namespace Base
{

using type_to_property_computer = std::map<PropertyComputerType, std::function<
        boost::any (graph_types::graph& g)> >;

static type_to_property_computer s_type_to_property_computer = {
    std::make_pair(CONNECTED_COMPONENTS,
        [] (graph_types::graph& g) -> ConnectedComponents::BaseType* {
            return new ConnectedComponents(g);
        }),
    std::make_pair(SHORTEST_PATH,
        [] (graph_types::graph& g) -> ShortestPath::BaseType* {
            return new ShortestPath(g);
        }),
    std::make_pair(BETWEENNESS_CENTRALITY,
        [] (graph_types::graph& g) -> BC::BaseType* {
            return new BC(g);
        }),
    std::make_pair(DEGREE,
        [] (graph_types::graph& g) -> DegreeComputer::BaseType* {
            return new DegreeComputer(g);
        }),
    std::make_pair(EIGEN_VALUES,
        [] (graph_types::graph& g) -> EigenValues::BaseType* {
            return new EigenValues(g);
        })
};

template <class ResType>
PropertyComputerBase<ResType>*
property_computer_factory::get_computer(graph_types::graph& graph,
                                        PropertyComputerType t)
{
    auto it = s_type_to_property_computer.find(t);
    assert(s_type_to_property_computer.end() != it);
    return (it->second)(graph);
}

} // namespace Base
