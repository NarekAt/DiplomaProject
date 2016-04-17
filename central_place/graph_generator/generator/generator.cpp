/**
 * @file generator/generator.cpp
 * @brief definition of generator class.
 */

#include "generator.h"
#include "graph_constants.h"
#include <iostream>
#include <random>
#include <ctime>
#include <assert.h>

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/graph_generators.h>

namespace {

unsigned fill_edges(graph_types::graph& g, const double p)
{
	std::random_device rd;
	graph_types::random_generator gen(rd());
	std::bernoulli_distribution d(p);
    const auto s = g.size();
    unsigned e_c = 0;
    for (graph_types::vertex i = graph_types::constants::VERTEX_0;
        i < s - graph_types::vertex(1); ++i) {
        for (graph_types::vertex j = i + graph_types::vertex(1); j < s; ++j) {
            if (true == d(gen)) {
                ++e_c;
                g.add_edge(i, j);
            }
        }
    }
    return e_c;
}

void fill_edges(graph_types::graph& g, const graph_types::graph_size numberOfEdges)
{
    ogdf::Graph graph;
    ogdf::randomHierarchy(graph, g.size(), numberOfEdges, false, false, false);

    ogdf::SListPure<ogdf::edge> edges;
    graph.allEdges(edges);

    ogdf::edge e;
    forall_edges(e, graph)
    {
        g.add_edge(e->source()->index(), e->target()->index());
	}
}

}

graph_types::graph generator::run(const graph_types::graph_size s, const double p,
    const graph_types::storage_core_type t, std::ofstream& logger) const
{
    time_t c_t = time(0);
    logger << "\n>>>>> Generation Started: " << ctime(&c_t);
    graph_types::graph g;
 
    assert(graph_types::storage_core_type::INVALID_CT != t);
    assert(0.0 <= p && 1.0 >= p);
    if (graph_types::storage_core_type::AUTODETECT == t) {
        g = graph_types::graph(s, p);
    } else {
        g = graph_types::graph(s, t);
    }
    const unsigned edge_count = fill_edges(g, p);
    c_t = time(0);
    logger << "\n>>>>> Generation Finished: " << ctime(&c_t);
    logger << "\n>>>>> Generated graph contains " << edge_count << " edges";
    return g;
}

graph_types::graph generator::run(const graph_types::graph_size numberOfVertices,
                       const graph_types::graph_size numberOfEdges,
                       const graph_types::storage_core_type t,
                       std::ofstream& logger) const
{
    time_t c_t = time(0);
    logger << "\n>>>>> Generation Started: " << ctime(&c_t);

    graph_types::graph g;
    assert(graph_types::storage_core_type::INVALID_CT != t);

    g = graph_types::graph(numberOfVertices, t);

    fill_edges(g, numberOfEdges);

    c_t = time(0);
    logger << "\n>>>>> Generation Finished: " << ctime(&c_t);
    return g;

}

