/**
 * @file property_counters/quadrangle_counter.cpp
 * @brief definition of quadrangle_counter class.
 */

#include "quadrangle_counter.h"
#include "utility.h"
#include "graph.h"
#include <vector>

// TODO: try to make faster.
unsigned quadrangle_counter::compute_initial_count() const
{
    unsigned num = 0;
    const auto edges = m_graph.edges_sequence();
    for (const auto& e : edges) {
        const graph_types::vertex vs = e.first;
        const graph_types::vertex vt = e.second;
        const auto vs_n = m_graph.neighbors_sequence(vs);
        const auto vt_n = m_graph.neighbors_sequence(vt);
        for (const auto& vsi : vs_n) {
            for (const auto& vti : vt_n) {
                if (vsi != vti && vsi != vt && vti != vs &&
                        m_graph.edge_exists(vsi, vti)) {
                    ++num;
                }
            }
        }
    }
    return num / 4;
}

unsigned quadrangle_counter::compute_decrease_after_remove(
    const graph_types::sequent_null_edges& e) const
{
    unsigned d_c = 0;
    for (const auto& n_e : e) {
        const graph_types::vertex vs = n_e.first;
        const graph_types::vertex vt = n_e.second;
        m_graph.remove_edge(vs, vt);
        const auto vs_n = m_graph.neighbors_sequence(vs);
        const auto vt_n = m_graph.neighbors_sequence(vt);
        for (const auto& vsi : vs_n) {
            for (const auto& vti : vt_n) {
                if (vsi != vti && m_graph.edge_exists(vsi, vti)) {
                    ++d_c;
                }
            }
        }
    }
    return d_c;
}

unsigned quadrangle_counter::compute_increase_after_add(
    const graph_types::sequent_null_edges& e) const
{
    // The same code for both: increase and decrease :)
    return compute_decrease_after_remove(e);
}

alternate_property_type quadrangle_counter::get_type() const
{
    return QUADRANGLE_COUNT;
}

quadrangle_counter::quadrangle_counter(
    graph_types::graph& graph)
    : property_counter_base(graph)
{}
