#pragma once

/**
 * @file graph_types/_graph_data_storage_bitsets_partial.h
 * @brief Declaration of graph_data_storage_bitsets_partial class
 */

#include "_graph_data_storage_base.h"
#include <boost/dynamic_bitset.hpp>

namespace graph_types
{

/**
 * @class graph_data_storage_bitsets_partial
 * @brief storage of data with partial connection list,
 *        neighbour vertices are stored into bitset.
 */
class graph_data_storage_bitsets_partial : public graph_data_storage_base
{
    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Constructor.
     * @param s Size of graph.
     */
    graph_data_storage_bitsets_partial(const graph_size& s);

    /**
     * @brief Copy-Constructor.
     * @param other storage to copy.
     */
    graph_data_storage_bitsets_partial(
        const graph_data_storage_bitsets_partial& other);

    /**
     * @brief Assignment operator.
     * @param other storage to assign.
     */
    graph_data_storage_bitsets_partial& operator=(
        const graph_data_storage_bitsets_partial& other);
    /// @}

public:
    /**
     * @typedef storage_type
     * @brief container type of data.
     */
    typedef std::vector<boost::dynamic_bitset<>> storage_type;

private:
    virtual graph_size impl_size() const;

private:
    virtual bool impl_edge_exists(const vertex& v1, const vertex& v2) const;
    bool strict_edge_exists(const vertex& v1, const vertex& v2) const;

private:
    virtual graph_size impl_degree(const vertex& v) const;

private:
    virtual set_of_vertices impl_neighbors_set(const vertex& v) const;
    void collect_less_neighbors_set(const vertex& v, set_of_vertices& result) const;

private:
    virtual sequence_of_vertices impl_neighbors_sequence(const vertex& v) const;
    void collect_less_neighbors_sequence(
        const vertex& v, sequence_of_vertices& result) const;

private:
    virtual set_of_edges impl_neighbor_edges_set(const vertex& v) const;
    void collect_less_neighbor_edges_set(
        const vertex& v, set_of_edges& result) const;

private:
    virtual sequence_of_edges impl_neighbor_edges_sequence(const vertex& v) const;
    void collect_less_neighbor_edges_sequence(
        const vertex& v, sequence_of_edges& result) const;

private:
    virtual set_of_edges impl_edges_set() const;
    virtual sequence_of_edges impl_edges_sequence() const;
    virtual edge impl_get_edge_by_index(unsigned long i) const;

private:
    virtual void impl_add_edge(const vertex& v1, const vertex& v2);
    void strict_add_edge(const vertex& v1, const vertex& v2);

private:
    virtual void impl_remove_edge(const vertex& v1, const vertex& v2);
    void strict_remove_edge(const vertex& v1, const vertex& v2);

private:
    virtual void impl_save(boost::archive::text_oarchive& ar) const;
    virtual void impl_save(boost::archive::binary_oarchive& ar) const;
    virtual void impl_save(boost::mpi::packed_oarchive& ar) const;
    virtual void impl_load(boost::archive::text_iarchive& ar);
    virtual void impl_load(boost::archive::binary_iarchive& ar);
    virtual void impl_load(boost::mpi::packed_iarchive& ar);

private:
    virtual void reset(const graph_size& s);

private:
    storage_type m_data;
};

}
