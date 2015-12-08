/**
 * @file randomizers/randomizator_factory.cpp 
 * @brief definition of randomizator_factory class
 */

#include "randomizator_factory.h"
#include "random_switch_randomizer.h"
#include "fixed_degree_randomizer.h"
#include <assert.h>
#include <functional>

typedef std::map<randomization_type, std::function<randomizator_base* 
    (graph_types::graph& graph,
    graph_types::sequent_null_edges& n_e_e)>> type_to_randomizator;

static type_to_randomizator s_type_to_randomizator = {
    std::make_pair(FIXED_DEGREE,
        [] (graph_types::graph& g,
            graph_types::sequent_null_edges& n_e_e) -> randomizator_base* {
            return new fixed_degree_randomizer(g, n_e_e);
        }),
    std::make_pair(RANDOM_SWITCH,
        [] (graph_types::graph& g,
            graph_types::sequent_null_edges& n_e_e) -> randomizator_base* {
            return new random_switch_randomizer(g, n_e_e);
        })
};

randomizator_base* randomizator_factory::get_randomizator(
    graph_types::graph& graph,
    graph_types::sequent_null_edges& non_existing_edges, randomization_type t)
{
    auto it = s_type_to_randomizator.find(t);
    assert(s_type_to_randomizator.end() != it);
    return (it->second)(graph, non_existing_edges);
}
