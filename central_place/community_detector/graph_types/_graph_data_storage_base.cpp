/**
 * @file graph_types/_graph_data_storage_base.h
 * @brief Definition of graph_data_storage_base abstract class.
 */

#include "_graph_data_storage_base.h"
#include <assert.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>

namespace graph_types
{

graph_size graph_data_storage_base::size() const
{
    return impl_size();
}

bool graph_data_storage_base::edge_exists(const vertex& v1, const vertex& v2) const
{
    assert(v1 != v2);
    return impl_edge_exists(v1, v2);
}

bool graph_data_storage_base::edge_exists(const edge& e) const
{
    assert(e.first != e.second);
    return impl_edge_exists(e.first, e.second);
}

graph_size graph_data_storage_base::degree(const vertex& v) const
{
    return impl_degree(v);
}

set_of_vertices graph_data_storage_base::neighbors_set(const vertex& v) const
{
    return impl_neighbors_set(v);
}

sequence_of_vertices graph_data_storage_base::neighbors_sequence(const vertex& v) const
{
    return impl_neighbors_sequence(v);
}

set_of_edges graph_data_storage_base::neighbor_edges_set(const vertex& v) const
{
    return impl_neighbor_edges_set(v);
}

sequence_of_edges graph_data_storage_base::neighbor_edges_sequence(const vertex& v) const
{
    return impl_neighbor_edges_sequence(v);
}

set_of_edges graph_data_storage_base::edges_set() const
{
    return impl_edges_set();
}

sequence_of_edges graph_data_storage_base::edges_sequence() const
{
    return impl_edges_sequence();
}

edge graph_data_storage_base::random_edge(random_generator& r_g) const
{
    assert(0 != m_edges_count);
    std::uniform_int_distribution<unsigned long> dist(0, m_edges_count - 1);
    unsigned long index = dist(r_g);
    return impl_get_edge_by_index(index);
}

void graph_data_storage_base::add_edge(const vertex& v1, const vertex& v2)
{
    assert(v1 != v2);
    impl_add_edge(v1, v2);
    ++m_edges_count;
}

void graph_data_storage_base::add_edge(const edge& e)
{
    assert(e.first != e.second);
    impl_add_edge(e.first, e.second);
    ++m_edges_count;
}

void graph_data_storage_base::add_edge_if_does_not_exist(const vertex& v1, const vertex& v2)
{
    assert(v1 != v2);
    if (!impl_edge_exists(v1, v2)) {
        impl_add_edge(v1, v2);
        ++m_edges_count;
    }
}

void graph_data_storage_base::add_edge_if_does_not_exist(const edge& e)
{
    assert(e.first != e.second);
    if (!impl_edge_exists(e.first, e.second)) {
        impl_add_edge(e.first, e.second);
        ++m_edges_count;
    }
}

void graph_data_storage_base::remove_edge(const vertex& v1, const vertex& v2)
{
    assert(v1 != v2);
    impl_remove_edge(v1, v2);
    assert(0 != m_edges_count);
    --m_edges_count;
}

void graph_data_storage_base::remove_edge(const edge& e)
{
    assert(e.first != e.second);
    impl_remove_edge(e.first, e.second);
    assert(0 != m_edges_count);
    --m_edges_count;
}

void graph_data_storage_base::remove_edge_if_exists(const vertex& v1, const vertex& v2)
{
    assert(v1 != v2);
    if (impl_edge_exists(v1, v2)) {
        impl_remove_edge(v1, v2);
        assert(0 != m_edges_count);
        --m_edges_count;
    }
}

void graph_data_storage_base::remove_edge_if_exists(const edge& e)
{
    assert(e.first != e.second);
    if (impl_edge_exists(e.first, e.second)) {
        impl_remove_edge(e.first, e.second);
        assert(0 != m_edges_count);
        --m_edges_count;
    }
}

storage_core_type graph_data_storage_base::core_type() const
{
    return m_core_type;
}

void graph_data_storage_base::save(boost::archive::text_oarchive& ar) const
{
    ar << m_edges_count;
    impl_save(ar);
}

void graph_data_storage_base::save(boost::archive::binary_oarchive& ar) const
{
    ar << m_edges_count;
    impl_save(ar);
}

void graph_data_storage_base::save(boost::mpi::packed_oarchive& ar) const
{
    ar << m_edges_count;
    impl_save(ar);
}

void graph_data_storage_base::load(boost::archive::text_iarchive& ar)
{
    ar >> m_edges_count;
    impl_load(ar);
}

void graph_data_storage_base::load(boost::archive::binary_iarchive& ar)
{
    ar >> m_edges_count;
    impl_load(ar);
}

void graph_data_storage_base::load(boost::mpi::packed_iarchive& ar)
{
    ar >> m_edges_count;
    impl_load(ar);
}

}
