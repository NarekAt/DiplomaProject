/**
 * @file graph_types/_graph_data_storage_sorted_vectors_full.cpp
 * @brief Definition of graph_data_storage_sorted_vectors_full class
 */

#include "_graph_data_storage_sorted_vectors_full.h"
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

graph_data_storage_sorted_vectors_full::graph_data_storage_sorted_vectors_full(
    const graph_size& s)
{
    m_core_type = storage_core_type::SORTED_VECTORS_FULL;
    m_edges_count = 0;
    m_data.resize(s);
}

graph_data_storage_sorted_vectors_full::graph_data_storage_sorted_vectors_full(
    const graph_data_storage_sorted_vectors_full& other) :
    m_data(other.m_data)
{
    m_core_type = storage_core_type::SORTED_VECTORS_FULL;
    m_edges_count = other.m_edges_count;
}

graph_data_storage_sorted_vectors_full& graph_data_storage_sorted_vectors_full::operator=(
    const graph_data_storage_sorted_vectors_full& other)
{
    m_data = other.m_data;
    m_edges_count = other.m_edges_count;
}

graph_size graph_data_storage_sorted_vectors_full::impl_size() const
{
    return m_data.size();
}

bool graph_data_storage_sorted_vectors_full::impl_edge_exists(
    const vertex& v1, const vertex& v2) const
{
    const auto& neighbours = m_data[v1];
    if (neighbours.empty()) {
        return false;
    }
    return std::binary_search(neighbours.begin(), neighbours.end(), v2);
}

set_of_vertices graph_data_storage_sorted_vectors_full::impl_neighbors_set(
    const vertex& v) const
{
    const auto& neighbours = m_data[v];
    set_of_vertices result;
    if (!neighbours.empty()) {
        for (const auto& n : neighbours) {
            result.insert(n);
        }
    }
    return result;
}

sequence_of_vertices graph_data_storage_sorted_vectors_full::impl_neighbors_sequence(
    const vertex& v) const
{
    return m_data[v];
}

set_of_edges graph_data_storage_sorted_vectors_full::impl_neighbor_edges_set(
    const vertex& v) const
{
    const auto& neighbours = m_data[v];
    set_of_edges result;
    if (!neighbours.empty()) {
        for (const auto& n : neighbours) {
            result.insert(edge(v, n));
        }
    }
    return result;
}

sequence_of_edges graph_data_storage_sorted_vectors_full::impl_neighbor_edges_sequence(
    const vertex& v) const
{
    const auto& neighbours = m_data[v];
    sequence_of_edges result;
    if (!neighbours.empty()) {
        for (const auto& n : neighbours) {
            result.push_back(edge(v, n));
        }
    }
    return result;
}

set_of_edges graph_data_storage_sorted_vectors_full::impl_edges_set() const
{
    set_of_edges results;
    const auto l = m_data.size() - 1;
    for (graph_size i = l; i >= constants::VERTEX_0; --i) {
        const auto& n = m_data[i];
        for (const auto& v : n) {
            if (v >= i) {
                break;
            }
            results.insert(edge(v, i));
        }
    }
    return results;
}

sequence_of_edges graph_data_storage_sorted_vectors_full::impl_edges_sequence() const
{
    sequence_of_edges results;
    const auto l = m_data.size() - 1;
    for (graph_size i = l; i >= constants::VERTEX_0; --i) {
        const auto& n = m_data[i];
        for (const auto& v : n) {
            if (v >= i) {
                break;
            }
            results.push_back(edge(v, i));
        }
    }
    return results;
}

edge graph_data_storage_sorted_vectors_full::impl_get_edge_by_index(
    unsigned long index) const
{
    const auto l = m_data.size() - 1;
    for (graph_size i = l; i >= constants::VERTEX_0; --i) {
        const auto& n = m_data[i];
        for (const auto& v : n) {
            if (v >= i) {
                break;
            }
            if (0 == index) {
                return edge(v, i);
            }
            --index;
        }
    }
    assert(!"Edge with index must be found");
}

void graph_data_storage_sorted_vectors_full::impl_add_edge(
    const vertex& v1, const vertex& v2)
{
    one_way_add_edge(v1, v2);
    one_way_add_edge(v2, v1);
}

void graph_data_storage_sorted_vectors_full::one_way_add_edge(
    const vertex& v1, const vertex& v2)
{
    auto& v1_neighbours = m_data[v1];
    if (v1_neighbours.empty()) {
        v1_neighbours.push_back(v2);
        return;
    }
    auto v2_it = std::lower_bound(v1_neighbours.begin(), v1_neighbours.end(), v2);
    assert(v1_neighbours.end() == v2_it || v2 < *v2_it);
    v1_neighbours.insert(v2_it, v2);
}

void graph_data_storage_sorted_vectors_full::impl_remove_edge(
    const vertex& v1, const vertex& v2)
{
    one_way_remove_edge(v1, v2);
    one_way_remove_edge(v2, v1);
}

void graph_data_storage_sorted_vectors_full::one_way_remove_edge(
    const vertex& v1, const vertex& v2)
{
    auto& v1_neighbours = m_data[v1];
    if (!v1_neighbours.empty()) {
        auto v2_it = std::lower_bound(v1_neighbours.begin(), v1_neighbours.end(), v2);
        assert(v1_neighbours.end() != v2_it && v2 == *v2_it);
        v1_neighbours.erase(v2_it);
    }
}

void graph_data_storage_sorted_vectors_full::impl_save(
    boost::archive::text_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_sorted_vectors_full::impl_save(
    boost::archive::binary_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_sorted_vectors_full::impl_save(
    boost::mpi::packed_oarchive& ar) const
{
    ar << m_data;
}

void graph_data_storage_sorted_vectors_full::impl_load(
    boost::archive::text_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_sorted_vectors_full::impl_load(
    boost::archive::binary_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_sorted_vectors_full::impl_load(
    boost::mpi::packed_iarchive& ar)
{
    ar >> m_data;
}

void graph_data_storage_sorted_vectors_full::reset(const graph_size& s)
{
    m_edges_count = 0;
    m_data.clear();
    m_data.resize(s);
}

}
