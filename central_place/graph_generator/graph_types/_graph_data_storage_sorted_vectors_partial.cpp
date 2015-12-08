/**
 * @file graph_types/_graph_data_storage_sorted_vectors_partial.cpp
 * @brief Definition of graph_data_storage_sorted_vectors_partial class
 */

#include "_graph_data_storage_sorted_vectors_partial.h"
#include "graph_constants.h"
#include <algorithm>
#include <assert.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/serialization/vector.hpp>

namespace graph_types
{

graph_data_storage_sorted_vectors_partial::graph_data_storage_sorted_vectors_partial(
    const graph_size& s)
{
    m_core_type = storage_core_type::SORTED_VECTORS_PARTIAL;
    m_edges_count = 0;
    m_data.resize(s);
}

graph_data_storage_sorted_vectors_partial::graph_data_storage_sorted_vectors_partial(
    const graph_data_storage_sorted_vectors_partial& other) :
    m_data(other.m_data)
{
    m_core_type = storage_core_type::SORTED_VECTORS_PARTIAL;
    m_edges_count = 0;
}

graph_data_storage_sorted_vectors_partial& graph_data_storage_sorted_vectors_partial::
    operator=(
        const graph_data_storage_sorted_vectors_partial& other)
{
    m_data = other.m_data;
    m_edges_count = other.m_edges_count;
}

graph_size graph_data_storage_sorted_vectors_partial::impl_size() const
{
    return m_data.size();
}

bool graph_data_storage_sorted_vectors_partial::impl_edge_exists(
    const vertex& v1, const vertex& v2) const
{
    if (v1 < v2) {
        return strict_edge_exists(v1, v2);
    } else {
        return strict_edge_exists(v2, v1);
    }
}

bool graph_data_storage_sorted_vectors_partial::strict_edge_exists(
    const vertex& v1, const vertex& v2) const
{
    assert(v1 < v2);
    const auto& neighbours = m_data[v1];
    if (neighbours.empty()) {
        return false;
    }
    return std::binary_search(neighbours.begin(), neighbours.end(), v2);
}

set_of_vertices graph_data_storage_sorted_vectors_partial::impl_neighbors_set(
    const vertex& v) const
{
    set_of_vertices result;
    collect_less_neighbors_set(v, result);
    const auto& neighbours = m_data[v];
    if (!neighbours.empty()) {
        for (const auto& n : neighbours) {
            result.insert(n);
        }
    }
    return result;
}

void graph_data_storage_sorted_vectors_partial::collect_less_neighbors_set(
    const vertex& v, set_of_vertices& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.insert(v_less);
        }
    }
}

sequence_of_vertices graph_data_storage_sorted_vectors_partial::impl_neighbors_sequence(
    const vertex& v) const
{
    sequence_of_vertices result;
    collect_less_neighbors_sequence(v, result);
    const auto& neighbours = m_data[v];
    if (!neighbours.empty()) {
        result.insert(result.end(), neighbours.begin(), neighbours.end());
    }
    return result; 
}

void graph_data_storage_sorted_vectors_partial::collect_less_neighbors_sequence(
    const vertex& v, sequence_of_vertices& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.push_back(v_less);
        }
    }
}

set_of_edges graph_data_storage_sorted_vectors_partial::impl_neighbor_edges_set(
    const vertex& v) const
{
    set_of_edges result;
    collect_less_neighbor_edges_set(v, result);
    const auto& neighbours = m_data[v];
    if (!neighbours.empty()) {
        for (const auto& n : neighbours) {
            result.insert(edge(v, n));
        }
    }
    return result;
}

void graph_data_storage_sorted_vectors_partial::collect_less_neighbor_edges_set(
    const vertex& v, set_of_edges& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.insert(edge(v_less, v));
        }
    }
}

sequence_of_edges graph_data_storage_sorted_vectors_partial::impl_neighbor_edges_sequence(
    const vertex& v) const
{
    sequence_of_edges result;
    collect_less_neighbor_edges_sequence(v, result);
    const auto& neighbours = m_data[v];
    if (!neighbours.empty()) {
        for (const auto& n : neighbours) {
            result.push_back(edge(v, n));
        }
    }
    return result;
}

void graph_data_storage_sorted_vectors_partial::collect_less_neighbor_edges_sequence(
    const vertex& v, sequence_of_edges& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.push_back(edge(v_less, v));
        }
    }
}

set_of_edges graph_data_storage_sorted_vectors_partial::impl_edges_set() const
{
    set_of_edges results;
    const auto s = graph_size(m_data.size());
    for (graph_size i = 0; i < s; ++i) {
        const auto& n = m_data[i];
        for (const auto& v : n) {
            results.insert(edge(i, v));
        }
    }
    return results;
}

sequence_of_edges graph_data_storage_sorted_vectors_partial::impl_edges_sequence() const
{
    sequence_of_edges results;
    const auto s = graph_size(m_data.size());
    for (graph_size i = 0; i < s; ++i) {
        const auto& n = m_data[i];
        for (const auto& v : n) {
            results.push_back(edge(i, v));
        }
    }
    return results;
}

edge graph_data_storage_sorted_vectors_partial::impl_get_edge_by_index(
    unsigned long index) const
{
    const auto s = graph_size(m_data.size());
    for (graph_size i = 0; i < s; ++i) {
        const auto& n = m_data[i];
        for (const auto& v : n) {
            if (0 == index) {
                return edge(i, v);
            }
            --index;
        }
    }
    assert(!"Edge with index must be found");
}

void graph_data_storage_sorted_vectors_partial::impl_add_edge(
    const vertex& v1, const vertex& v2)
{
    if (v1 < v2) {
        strict_add_edge(v1, v2);
    } else {
        strict_add_edge(v2, v1);
    }
}

void graph_data_storage_sorted_vectors_partial::strict_add_edge(
    const vertex& v1, const vertex& v2)
{
    assert(v1 < v2);
    auto& v1_neighbours = m_data[v1];
    if (v1_neighbours.empty()) {
        v1_neighbours.push_back(v2);
        return;
    }
    auto v2_it = std::lower_bound(v1_neighbours.begin(), v1_neighbours.end(), v2);
    assert(v1_neighbours.end() == v2_it || v2 < *v2_it);
    v1_neighbours.insert(v2_it, v2);
}

void graph_data_storage_sorted_vectors_partial::impl_remove_edge(
    const vertex& v1, const vertex& v2)
{
    if (v1 < v2) {
        strict_remove_edge(v1, v2);
    } else {
        strict_remove_edge(v2, v1);
    }
}

void graph_data_storage_sorted_vectors_partial::strict_remove_edge(
    const vertex& v1, const vertex& v2)
{
    assert(v1 < v2);
    auto& v1_neighbours = m_data[v1];
    if (!v1_neighbours.empty()) {
        auto v2_it = std::lower_bound(v1_neighbours.begin(), v1_neighbours.end(), v2);
        assert(v1_neighbours.end() != v2_it && v2 == *v2_it);
        v1_neighbours.erase(v2_it);
    }
}

void graph_data_storage_sorted_vectors_partial::impl_save(
    boost::archive::text_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_sorted_vectors_partial::impl_save(
    boost::archive::binary_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_sorted_vectors_partial::impl_save(
    boost::mpi::packed_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_sorted_vectors_partial::impl_load(
    boost::archive::text_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_sorted_vectors_partial::impl_load(
    boost::archive::binary_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_sorted_vectors_partial::impl_load(
    boost::mpi::packed_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_sorted_vectors_partial::reset(const graph_size& s)
{
    m_edges_count = 0;
    m_data.clear();
    m_data.resize(s);
}

}
