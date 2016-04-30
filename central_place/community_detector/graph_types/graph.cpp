/**
 * @file graph_types/graph.cpp
 * @breiff Definition of graph class
 */

#include "graph.h"

namespace graph_types
{

graph_size graph::size() const
{
    assert(nullptr != m_data);
    return m_data->size();
}

bool graph::edge_exists(const vertex& v1, const vertex& v2) const
{
    assert(nullptr != m_data);
    return m_data->edge_exists(v1, v2);
}

bool graph::edge_exists(const edge& e) const
{
    assert(nullptr != m_data);
    return m_data->edge_exists(e);
}

graph_size graph::degree(const vertex& v) const
{
    assert(nullptr != m_data);
    return m_data->degree(v);
}

set_of_vertices graph::neighbors_set(const vertex& v) const
{
    assert(nullptr != m_data);
    return m_data->neighbors_set(v);
}

sequence_of_vertices graph::neighbors_sequence(const vertex& v) const
{
    assert(nullptr != m_data);
    return m_data->neighbors_sequence(v);
}

set_of_edges graph::neighbor_edges_set(const vertex& v) const
{
    assert(nullptr != m_data);
    return m_data->neighbor_edges_set(v);
}

sequence_of_edges graph::neighbor_edges_sequence(const vertex& v) const
{
    assert(nullptr != m_data);
    return m_data->neighbor_edges_sequence(v);
}

set_of_edges graph::edges_set() const
{
    assert(nullptr != m_data);
    return m_data->edges_set();
}

sequence_of_edges graph::edges_sequence() const
{
    assert(nullptr != m_data);
    return m_data->edges_sequence();
}

edge graph::random_edge(random_generator& r_g) const
{
    assert(nullptr != m_data);
    return m_data->random_edge(r_g);
}

void graph::add_edge(const vertex& v1, const vertex& v2)
{
    assert(nullptr != m_data);
    m_data->add_edge(v1, v2);
}

void graph::add_edge(const edge& e)
{
    assert(nullptr != m_data);
    m_data->add_edge(e);
}

void graph::remove_edge(const vertex& v1, const vertex& v2)
{
    assert(nullptr != m_data);
    m_data->remove_edge(v1, v2);
}

void graph::remove_edge(const edge& e)
{
    assert(nullptr != m_data);
    m_data->remove_edge(e);
}

graph::graph()
{
    m_data = data_storage_factory::create(0, storage_core_type::BITSETS_FULL);
}

graph::graph(const storage_core_type t)
{
    m_data = data_storage_factory::create(0, t);
}

graph::graph(const graph_size s, const storage_core_type t)
{
    m_data = data_storage_factory::create(s, t);
}

graph::graph(const graph_size s, const double p)
{
    m_data = data_storage_factory::create(s, p);
}

graph::graph(const graph& o)
{
    m_data = data_storage_factory::create_core_data_copy_from_src(o.m_data);
}

graph::graph(graph&& o)
{
    m_data = o.m_data;
    o.m_data = nullptr;
}

graph::~graph()
{
    if (nullptr != m_data) {
        delete m_data;
    }
}

graph& graph::operator=(const graph& o)
{
    data_storage_factory::copy_core_data_from_src_to_dest(o.m_data, m_data);
    return *this;
}

graph& graph::operator=(graph&& o)
{
    assert(nullptr != m_data);
    delete m_data;
    m_data = o.m_data;
    o.m_data = nullptr;
    return *this;
}

}
