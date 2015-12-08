/**
 * @file graph_types/_graph_data_storage_bitsets_full.cpp
 * @brief Definition of graph_data_storage_bitsets_full class
 */

#include "_graph_data_storage_bitsets_full.h"
#include "_boost_dynamic_bitset_serialization.h"
#include "graph_constants.h"
#include <algorithm>
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

}

graph_data_storage_bitsets_full::graph_data_storage_bitsets_full(
    const graph_size& s)
{
    m_core_type = storage_core_type::BITSETS_FULL;
    m_edges_count = 0;
    m_data.resize(s, boost::dynamic_bitset<>(s));
}

graph_data_storage_bitsets_full::graph_data_storage_bitsets_full(
    const graph_data_storage_bitsets_full& other) :
    m_data(other.m_data)
{
    m_core_type = storage_core_type::BITSETS_FULL;
    m_edges_count = other.m_edges_count;
}

graph_data_storage_bitsets_full& graph_data_storage_bitsets_full::operator=(
    const graph_data_storage_bitsets_full& other)
{
    m_data = other.m_data;
    m_edges_count = other.m_edges_count;
}

graph_size graph_data_storage_bitsets_full::impl_size() const
{
    return m_data.size();
}

bool graph_data_storage_bitsets_full::impl_edge_exists(
    const vertex& v1, const vertex& v2) const
{
    const auto& neighbours = m_data[v1];
    assert(v2 < vertex(neighbours.size()));
    return neighbours[v2];
}

set_of_vertices graph_data_storage_bitsets_full::impl_neighbors_set(
    const vertex& v) const
{
    const auto& neighbours = m_data[v];
    set_of_vertices result;
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.insert(vertex(i));
        }
    }
    return result;
}

sequence_of_vertices graph_data_storage_bitsets_full::impl_neighbors_sequence(
    const vertex& v) const
{
    const auto& neighbours = m_data[v];
    sequence_of_vertices result;
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.push_back(vertex(i));
        }
    }
    return result;
}

set_of_edges graph_data_storage_bitsets_full::impl_neighbor_edges_set(
    const vertex& v) const
{
    const auto& neighbours = m_data[v];
    set_of_edges result;
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.insert(edge(vertex(i), v));
        }
    }
    return result;
}

sequence_of_edges graph_data_storage_bitsets_full::impl_neighbor_edges_sequence(
    const vertex& v) const
{
    const auto& neighbours = m_data[v];
    sequence_of_edges result;
    for (bitset_size_type i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i]) {
            result.push_back(edge(vertex(i), v));
        }
    }
    return result;
}

set_of_edges graph_data_storage_bitsets_full::impl_edges_set() const
{
    set_of_edges results;
    const auto l = m_data.size() - 1;
    for (int i = l; i >= 0; --i) {
        const auto& n = m_data[i];
        for (bitset_size_type j = 0; j < static_cast<uint32_t>(i); ++j) {
            if (n[j]) {
                results.insert(edge(vertex(j), i));
            }
        }
    }
    return results;
}

sequence_of_edges graph_data_storage_bitsets_full::impl_edges_sequence() const
{
    sequence_of_edges results;
    const auto l = m_data.size() - 1;
    for (int i = l; i >= 0; --i) {
        const auto& n = m_data[i];
        for (bitset_size_type j = 0; j < static_cast<uint32_t>(i); ++j) {
            if (n[j]) {
                results.push_back(edge(vertex(j), i));
            }
        }
    }
    return results;
}

edge graph_data_storage_bitsets_full::impl_get_edge_by_index(
    unsigned long index) const
{
    const auto l = m_data.size() - 1;
    for (int i = l; i >= 0; --i) {
        const auto& n = m_data[i];
        for (bitset_size_type j = 0; j < static_cast<uint32_t>(i); ++j) {
            if (n[j]) {
                if (0 == index) {
                    return edge(vertex(j), i);
                }
                --index;
            }
        }
    }
    assert(!"Edge with index must be found");
}

void graph_data_storage_bitsets_full::impl_add_edge(
    const vertex& v1, const vertex& v2)
{
    one_way_add_edge(v1, v2);
    one_way_add_edge(v2, v1);
}

void graph_data_storage_bitsets_full::one_way_add_edge(
    const vertex& v1, const vertex& v2)
{
    auto& v1_neighbours = m_data[v1];
    auto index = static_cast<size_t>(v2);
    assert(!v1_neighbours[index]);
    v1_neighbours.set(index, true); 
}

void graph_data_storage_bitsets_full::impl_remove_edge(
    const vertex& v1, const vertex& v2)
{
    one_way_remove_edge(v1, v2);
    one_way_remove_edge(v2, v1);
}

void graph_data_storage_bitsets_full::one_way_remove_edge(
    const vertex& v1, const vertex& v2)
{
    auto& v1_neighbours = m_data[v1];
    auto index = static_cast<size_t>(v2);
    assert(v1_neighbours[index]);
    v1_neighbours.set(index, false); 
}

void graph_data_storage_bitsets_full::impl_save(
    boost::archive::text_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_bitsets_full::impl_save(
    boost::archive::binary_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_bitsets_full::impl_save(
    boost::mpi::packed_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_bitsets_full::impl_load(
    boost::archive::text_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_bitsets_full::impl_load(
    boost::archive::binary_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_bitsets_full::impl_load(
    boost::mpi::packed_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_bitsets_full::reset(const graph_size& s)
{
    m_edges_count = 0;
    m_data.clear();
    m_data.resize(s, boost::dynamic_bitset<>(s));
}

}
