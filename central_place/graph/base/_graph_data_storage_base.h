#pragma once

/**
 * @file base/_graph_data_storage_base.h
 * @brief Declaration of graph_data_storage_base abstract class.
 */

#include "types.h"

namespace boost {
    namespace archive {
        class text_oarchive;
        class text_iarchive;
        class binary_oarchive;
        class binary_iarchive;
    }
    namespace mpi {
        class packed_oarchive;
        class packed_iarchive;
    }
}

namespace graph_types
{

/**
 * @class graph_data_storage_base
 * @brief base class for storing graph data.
 */
class graph_data_storage_base
{
    /// @name Data access interface.
    /// @{
public:
    /**
     * @brief Gets the size of graph.
     */
    graph_size size() const;

    /**
     * @brief Checks if there is an edge which connects given vertices;
     * @param v1 First vertex.
     * @param v2 Second vertex.
     */
    bool edge_exists(const vertex& v1, const vertex& v2) const;

    /**
     * @brief Checks if there is an edge.
     * @param e Edge.
     */
    bool edge_exists(const edge& e) const;

    /**
     * @brief Gets neighbors set of the given vertex.
     * @param v Vertex for which neighbors are got.
     */
    set_of_vertices neighbors_set(const vertex& v) const;

    /**
     * @brief Gets neighbors sequence of the given vertex.
     * @param v Vertex for which neighbors are got.
     */
    sequence_of_vertices neighbors_sequence(const vertex& v) const;

    /**
     * @brief Gets neighbor-edges set of the given vertex.
     * @param t Vertex for which neighbor-edges are got.
     */
    set_of_edges neighbor_edges_set(const vertex& v) const;
    
    /**
     * @brief Gets neighbor-edges sequence of the given vertex.
     * @param v Vertex for which neighbor-edges are got.
     */
    sequence_of_edges neighbor_edges_sequence(const vertex& v) const;

    /**
     * @brief Gets all exist edges set of data.
     */
    set_of_edges edges_set() const;

    /**
     * @brief Gets all exist edges sequence of data.
     */
    sequence_of_edges edges_sequence() const;

    /**
     * @brief Gets random edge.
     * @param r_g Random generator.
     * @pre Graph should contain edges.
     */
    edge random_edge(random_generator& r_g) const;
    /// @}

    /// @name Edge adding interface.
    /// @{
public:
    /**
     * @brief Adds edge between given vertices.
     * @param v1 First vertex.
     * @param v2 Second vertex.
     * @pre edge should not exist.
     * @note To improve performence, it is suggested to give,
     *       v1 and v2 in ascending order.
     */
    void add_edge(const vertex& v1, const vertex& v2);

    /**
     * @brief Adds edge.
     * @param e Edge.
     * @pre edge should not exist.
     * @note To improve performence, it is suggested to give,
     *       edge which contains vertices with accending order.
     */
    void add_edge(const edge& e);

    /**
     * @brief Adds edge between given vertices if it doesn't exist.
     * @param v1 First vertex.
     * @param v2 Second vertex.
     * @note To improve performence, it is suggested to give,
     *       v1 and v2 in ascending order.
     * @note In release build this method will be slower then "add_edge"
     * @note This function should not be opened in graph class as interface
     *       to keep restriction of edge existance
     */
    void add_edge_if_does_not_exist(const vertex& v1, const vertex& v2);

    /**
     * @brief Adds edge if it doesn't exist.
     * @param e Edge.
     * @note To improve performence, it is suggested to give,
     *       edge which contains vertices with accending order.
     * @note In release build this method will be slower then "add_edge"
     * @note This function should not be opened in graph class as interface
     *       to keep restriction of edge existance
     */
    void add_edge_if_does_not_exist(const edge& e);
    /// @}

    /// @name Edge removing interface.
    /// @{
public:
    /**
     * @brief Remove edge which connects given vertices.
     * @param v1 First vertex of edge.
     * @param v2 Second vertex of edge.
     * @pre edge should exist.
     * @note To improve performence, it is suggested to give,
     *       v1 and v2 in ascending order.
     */
    void remove_edge(const vertex& v1, const vertex& v2);

    /**
     * @brief removes edge.
     * @param e Edge.
     * @pre edge should exist.
     * @note To improve performence, it is suggested to give,
     *       edge which contains vertices with accending order.
     */
    void remove_edge(const edge& e);

    /**
     * @brief Remove edge which connects given vertices if it exists.
     * @param v1 First vertex of edge.
     * @param v2 Second vertex of edge.
     * @note To improve performence, it is suggested to give,
     *       v1 and v2 in ascending order.
     * @note In release build this method will be slower then "remove_edge"
     * @note This function should not be opened in graph class as interface
     *       to keep restriction of edge existance
     */
    void remove_edge_if_exists(const vertex& v1, const vertex& v2);

    /**
     * @brief removes edge if it exists.
     * @param e Edge.
     * @note To improve performence, it is suggested to give,
     *       edge which contains vertices with accending order.
     * @note In release build this method will be slower then "remove_edge"
     * @note This function should not be opened in graph class as interface
     *       to keep restriction of edge existance
     */
    void remove_edge_if_exists(const edge& e);
    /// @}

    /// @name Serialization interface.
    /// @{
public:
    /**
     * @brief Saves data into boost text archive.
     * @param ar Archive.
     */
    void save(boost::archive::text_oarchive& ar) const;

    /**
     * @brief Saves data into boost binary archive.
     * @param ar Archive.
     */
    void save(boost::archive::binary_oarchive& ar) const;

    /**
     * @brief Saves data into boost boost mpi packed archive.
     * @param ar Archive.
     */
    void save(boost::mpi::packed_oarchive& ar) const;

    /**
     * @brief Loads data from boost text archive.
     * @param ar Archive.
     */
    void load(boost::archive::text_iarchive& ar);

    /**
     * @brief Loads data from boost binary archive.
     * @param ar Archive.
     */
    void load(boost::archive::binary_iarchive& ar);
    
    /**
     * @brief Loads data from boost boost mpi packed archive.
     * @param ar Archive.
     */
    void load(boost::mpi::packed_iarchive& ar);

public:
    /**
     * @breif Gets Core type.
     */
    storage_core_type core_type() const;

private:
    virtual graph_size impl_size() const = 0;
    virtual bool impl_edge_exists(const vertex& v1, const vertex& v2) const = 0;
    virtual set_of_vertices impl_neighbors_set(const vertex& v) const = 0;
    virtual sequence_of_vertices impl_neighbors_sequence(const vertex& v) const = 0;
    virtual set_of_edges impl_neighbor_edges_set(const vertex& v) const = 0;
    virtual sequence_of_edges impl_neighbor_edges_sequence(const vertex& v) const = 0;
    virtual set_of_edges impl_edges_set() const = 0;
    virtual sequence_of_edges impl_edges_sequence() const = 0;
    virtual edge impl_get_edge_by_index(unsigned long i) const = 0;
    virtual void impl_add_edge(const vertex& v1, const vertex& v2) = 0;
    virtual void impl_remove_edge(const vertex& v1, const vertex& v2) = 0;
    virtual void impl_save(boost::archive::text_oarchive& ar) const = 0;
    virtual void impl_save(boost::archive::binary_oarchive& ar) const = 0;
    virtual void impl_save(boost::mpi::packed_oarchive& ar) const = 0;
    virtual void impl_load(boost::archive::text_iarchive& ar) = 0;
    virtual void impl_load(boost::archive::binary_iarchive& ar) = 0;
    virtual void impl_load(boost::mpi::packed_iarchive& ar) = 0;

protected:
    storage_core_type m_core_type;
    unsigned long m_edges_count;

private:
    friend class data_storage_factory;

private:
    virtual void reset(const graph_size& s) = 0;
};

}
