/**
 * @file property_counters/property_counter_factory.cpp
 * @brief definition of property_counter_factory class
 */

#include "property_counter_factory.h"
#include "triangle_counter.h"
#include "quadrangle_counter.h"
#include "connected_triples_counter.h"
#include <assert.h>
#include <functional>

typedef std::map<alternate_property_type, std::function<
    property_counter_base* (graph_types::graph& g)>>
        type_to_property_counter;

static type_to_property_counter s_type_to_property_counter = {
    std::make_pair(TRIANGLE_COUNT,
        [] (graph_types::graph& g) -> property_counter_base* {
            return new triangle_counter(g);
        }),
    std::make_pair(QUADRANGLE_COUNT,
        [] (graph_types::graph& g) -> property_counter_base* {
            return new quadrangle_counter(g);
        }),
    std::make_pair(CONNECTED_TRIPLES_COUNT,
        [] (graph_types::graph& g) -> property_counter_base* {
            return new connected_triples_counter(g);
        })
};

property_counter_base* property_counter_factory::get_counter(
    graph_types::graph& graph, alternate_property_type t)
{
    auto it = s_type_to_property_counter.find(t);
    assert(s_type_to_property_counter.end() != it);
    return (it->second)(graph);
}
