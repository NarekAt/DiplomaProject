/**
 * @file randomizers/fixed_degree_randomizer.h
 * @brief definition of class fixed_degree_randomizer
 */

#include "fixed_degree_randomizer.h"
#include "graph.h"
#include <assert.h>

graph_types::remove_add_edges_pair fixed_degree_randomizer::get_step()
{
    graph_types::remove_add_edges_pair r_a_p;
    graph_types::edge e1;
    graph_types::vertex vs1;
    graph_types::vertex vt1;
    graph_types::edge e2;
    graph_types::vertex vs2;
    graph_types::vertex vt2;
    do {
        e1 = m_graph.random_edge(m_random_generator);
        vs1 = e1.first;
        vt1 = e1.second;
        e2 = m_graph.random_edge(m_random_generator);
        vs2 = e2.first;
        vt2 = e2.second;
    } while (e1 == e2 || vs1 == vs2 || vt1 == vt2 ||
        vs1 == vt2 || vt1 == vs2 ||
        m_graph.edge_exists(vs1, vs2) ||
        m_graph.edge_exists(vs1, vt2) ||
        m_graph.edge_exists(vt1, vt2) ||
        m_graph.edge_exists(vt1, vs2));
    assert(e1 != e2 && vs1 != vs2 && vt1 != vt2 &&
        vs1 != vt2 && vt1 != vs2 &&
        !m_graph.edge_exists(vs1, vs2) &&
        !m_graph.edge_exists(vs1, vt2) &&
        !m_graph.edge_exists(vt1, vt2) &&
        !m_graph.edge_exists(vt1, vs2));
    r_a_p.first.push_back(graph_types::edge(vs1, vt1));
    r_a_p.first.push_back(graph_types::edge(vs2, vt2));
    r_a_p.second.push_back(graph_types::edge(vs1, vs2));
    r_a_p.second.push_back(graph_types::edge(vt1, vt2));
    return r_a_p;
}

randomization_type fixed_degree_randomizer::get_type() const
{
    return FIXED_DEGREE;
}

fixed_degree_randomizer::fixed_degree_randomizer(
    graph_types::graph& graph,
    graph_types::sequent_null_edges& non_existing_edges) :
    randomizator_base(graph, non_existing_edges)
{}
