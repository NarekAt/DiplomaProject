/**
 * @file graph_types/_graph_data_storage_bitsets_partial.cpp
 * @brief Definition of graph_data_storage_bitsets_partial class
 */

#include "_graph_data_storage_bitsets_partial.h"
#include "graph_constants.h"
#include "_boost_dynamic_bitset_serialization.h"
#include <algorithm>
#include <assert.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>

namespace graph_types
{

namespace {

typedef boost::dynamic_bitset<>::size_type bitset_size_type;

/**
 * @brief Gets bitset index for partion bitsets.
 * @param v1 bitset owner vertex.
 * @param v2 neighbour of v1.
 * @pre v2 must be greater then v1.
 */
bitset_size_type bitset_index(const vertex& v1, const vertex& v2)
{
    assert(v1 < v2);
    return v2 - v1 - vertex(1);
}

/**
 * @brief Gets verex from partial bitset index.
 * @param v bitset owner vertex.
 * @param b_i bitset index.
 */
vertex vertex_from_index(const vertex& v, const bitset_size_type b_i)
{
    return v + vertex(1) + vertex(b_i);
}

}

graph_data_storage_bitsets_partial::graph_data_storage_bitsets_partial(
    const graph_size& s)
{
    m_core_type = storage_core_type::BITSETS_PARTIAL;
    m_edges_count = 0;
    bitset_size_type  bits_count = s - graph_size(1);
    do {
        m_data.push_back(boost::dynamic_bitset<>(bits_count--));
    } while (0 != bits_count);
    m_data.push_back(boost::dynamic_bitset<>(0));
}

graph_data_storage_bitsets_partial::graph_data_storage_bitsets_partial(
    const graph_data_storage_bitsets_partial& other) :
    m_data(other.m_data)
{
    m_core_type = storage_core_type::BITSETS_PARTIAL;
    m_edges_count = other.m_edges_count;
}

graph_data_storage_bitsets_partial& graph_data_storage_bitsets_partial::operator=(
    const graph_data_storage_bitsets_partial& other)
{
    m_data = other.m_data;
    m_edges_count = other.m_edges_count;
}

graph_size graph_data_storage_bitsets_partial::impl_size() const
{
    return m_data.size();
}

bool graph_data_storage_bitsets_partial::impl_edge_exists(
    const vertex& v1, const vertex& v2) const
{
    if (v1 < v2) {
        return strict_edge_exists(v1, v2);
    } else {
        return strict_edge_exists(v2, v1);
    }
}

bool graph_data_storage_bitsets_partial::strict_edge_exists(
    const vertex& v1, const vertex& v2) const
{
    assert(v1 < v2);
    const auto& neighbours = m_data[v1];
    bitset_size_type index = bitset_index(v1, v2);
    assert(index < neighbours.size());
    return neighbours[index];
}

graph_size graph_data_storage_bitsets_partial::impl_degree(
        const vertex& v) const
{
    const auto& neighbours = m_data[v];
    unsigned count;
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            ++count;
        }
    }
    return count;
}

set_of_vertices graph_data_storage_bitsets_partial::impl_neighbors_set(
    const vertex& v) const
{
    set_of_vertices result;
    collect_less_neighbors_set(v, result);
    const auto& neighbours = m_data[v];
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.insert(vertex_from_index(v, i));
        }
    }
    return result;
}

void graph_data_storage_bitsets_partial::collect_less_neighbors_set(
    const vertex& v, set_of_vertices& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.insert(v_less);
        }
    }
}

sequence_of_vertices graph_data_storage_bitsets_partial::impl_neighbors_sequence(
    const vertex& v) const
{
    sequence_of_vertices result;
    collect_less_neighbors_sequence(v, result);
    const auto& neighbours = m_data[v];
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.push_back(vertex_from_index(v, i));
        }
    }
    return result;
}

void graph_data_storage_bitsets_partial::collect_less_neighbors_sequence(
    const vertex& v, sequence_of_vertices& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.push_back(v_less);
        }
    }
}

set_of_edges graph_data_storage_bitsets_partial::impl_neighbor_edges_set(
    const vertex& v) const
{
    set_of_edges result;
    collect_less_neighbor_edges_set(v, result);
    const auto& neighbours = m_data[v];
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.insert(edge(v, vertex_from_index(v, i)));
        }
    }
    return result;
}

void graph_data_storage_bitsets_partial::collect_less_neighbor_edges_set(
    const vertex& v, set_of_edges& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.insert(edge(v_less, v));
        }
    }
}

sequence_of_edges graph_data_storage_bitsets_partial::impl_neighbor_edges_sequence(
    const vertex& v) const
{
    sequence_of_edges result;
    collect_less_neighbor_edges_sequence(v, result);
    const auto& neighbours = m_data[v];
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.push_back(edge(v, vertex_from_index(v, i)));
        }
    }
    return result;
}

void graph_data_storage_bitsets_partial::collect_less_neighbor_edges_sequence(
    const vertex& v, sequence_of_edges& result) const
{
    for (vertex v_less = constants::VERTEX_0; v > v_less; ++v_less) {
        if (strict_edge_exists(v_less, v)) {
            result.push_back(edge(v_less, v));
        }
    }
}

set_of_edges graph_data_storage_bitsets_partial::impl_edges_set() const
{
    set_of_edges results;
    const auto s = graph_size(m_data.size());
    for (graph_size i = 0; i < s; ++i) {
        const auto& n = m_data[i];
        for (bitset_size_type j = 0 ; j < n.size(); ++j) {
            if (n[i]) {
                results.insert(edge(i, vertex(j)));
            }
        }
    }
    return results;
}

sequence_of_edges graph_data_storage_bitsets_partial::impl_edges_sequence() const
{
    sequence_of_edges results;
    const auto s = graph_size(m_data.size());
    for (graph_size i = 0; i < s; ++i) {
        const auto& n = m_data[i];
        for (bitset_size_type j = 0 ; j < n.size(); ++j) {
            if (n[i]) {
                results.push_back(edge(i, vertex(j)));
            }
        }
    }
    return results;
}

edge graph_data_storage_bitsets_partial::impl_get_edge_by_index(
    unsigned long index) const
{
    const auto s = graph_size(m_data.size());
    for (graph_size i = 0; i < s; ++i) {
        const auto& n = m_data[i];
        for (bitset_size_type j = 0 ; j < n.size(); ++j) {
            if (n[i]) {
                if (0 == index) {
                    return edge(i, vertex(j));
                }
                --index;
            }
        }
    }
    assert(!"Edge with index must be found");
}

void graph_data_storage_bitsets_partial::impl_add_edge(
    const vertex& v1, const vertex& v2)
{
    if (v1 < v2) {
        strict_add_edge(v1, v2);
    } else {
        strict_add_edge(v2, v1);
    }
}

void graph_data_storage_bitsets_partial::strict_add_edge(
    const vertex& v1, const vertex& v2)
{
    assert(v1 < v2);
    auto& v1_neighbours = m_data[v1];
    auto index = bitset_index(v1, v2);
    assert(!v1_neighbours[index]);
    v1_neighbours.set(index, true);
}

void graph_data_storage_bitsets_partial::impl_remove_edge(
    const vertex& v1, const vertex& v2)
{
    if (v1 < v2) {
        strict_remove_edge(v1, v2);
    } else {
        strict_remove_edge(v2, v1);
    }
}

void graph_data_storage_bitsets_partial::strict_remove_edge(
    const vertex& v1, const vertex& v2)
{
    assert(v1 < v2);
    auto& v1_neighbours = m_data[v1];
    auto index = bitset_index(v1, v2);
    assert(v1_neighbours[index]);
    v1_neighbours.set(index, false);
}

void graph_data_storage_bitsets_partial::impl_save(
    boost::archive::text_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_bitsets_partial::impl_save(
    boost::archive::binary_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_bitsets_partial::impl_save(
    boost::mpi::packed_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_bitsets_partial::impl_load(
    boost::archive::text_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_bitsets_partial::impl_load(
    boost::archive::binary_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_bitsets_partial::impl_load(
    boost::mpi::packed_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_bitsets_partial::reset(const graph_size& s)
{
    m_edges_count = 0;
    m_data.clear();
    bitset_size_type bits_count = s - graph_size(1);
    do {
        m_data.push_back(boost::dynamic_bitset<>(bits_count--));
    } while (0 != bits_count);
    m_data.push_back(boost::dynamic_bitset<>(0));
}

}
