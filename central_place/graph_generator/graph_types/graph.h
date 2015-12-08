#pragma once

/**
 * @file graph_types/graph.h
 * @breiff Declaration of graph class
 */

#include "graph_types.h"
#include "_data_storage_factory.h"
#include "_graph_data_storage_base.h"
#include <assert.h>
#include <type_traits>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

namespace graph_types
{

/**
 * @class graph
 * @brief This class represents undirected graphs.
 */
class graph
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
     * @param r_g random generator.
     * @pre Graph should contain edges.
     */
    edge random_edge(random_generator& r_g) const;
    /// @}

    /// @name Date changing interface.
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
    /// @}

    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Default Constructor.
     * @note Constructs empty graph.
     */
    graph();
    
    /**
     * @brief Constructor. Creates empty graph with given storage core type.
     * @param t Storage core type.
     */
    graph(const storage_core_type t);

    /**
     * @brief Constructor.
     * @param s size of graph.
     * @param t Storage core type.
     */
    graph(const graph_size s, const storage_core_type t = storage_core_type::AUTODETECT);

    /**
     * @brief Constructor.
     * @param s size of graph.
     * @param p Existance probability of edge.
     * @note Storage core type will be autodetected.
     */
    graph(const graph_size s, const double p);

    /**
     * @brief Copy constructor.
     * @param o Other graph to copy.
     */
    graph(const graph& o);

    /**
     * @brief Move constructor.
     * @param o Other graph to move.
     */
    graph(graph&& o);

    /**
     * @brief Destructor.
     */
    ~graph();

    /**
     * @brief Assignment operator.
     * @param o Other graph to assign.
     */
    graph& operator=(const graph& o);

    /**
     * @brief Move Assignement operator.
     * @param o Other graph to move-assign.
     */
    graph& operator=(graph&& o);
    /// @}

    /// @name Boost serialization private interface.
    /// @{
private:
    friend class boost::serialization::access;

    template <class A>
    void save(A& ar, const unsigned int version) const;

    template <class A>
    void load(A& ar, const unsigned version);
    
    template <class A>
    void serialize(A& ar, const unsigned version);
    /// @}

private:
    graph_data_storage_base* m_data;
};

template <class A>
void graph::save(A& ar, const unsigned version) const
{
    static_assert(std::is_same<A, boost::archive::text_oarchive>::value ||
        std::is_same<A, boost::archive::binary_oarchive>::value ||
        std::is_same<A, boost::mpi::packed_oarchive>::value,
        "archive type should be text_oarchive or binary_oarchive");
    assert(nullptr != m_data);
    unsigned t_uint = static_cast<unsigned>(m_data->core_type());
    ar << t_uint;
    m_data->save(ar);
}

template <class A>
void graph::load(A& ar, const unsigned version)
{
    static_assert(std::is_same<A, boost::archive::text_iarchive>::value ||
        std::is_same<A, boost::archive::binary_iarchive>::value ||
        std::is_same<A, boost::mpi::packed_iarchive>::value,
        "archive type should be text_iarchive or binary_iarchive");
    storage_core_type t;
    unsigned t_uint = 0;
    ar >> t_uint;
    t = static_cast<storage_core_type>(t_uint);
    assert(nullptr != m_data);
    if (t != m_data->core_type()) {
        auto temp_data = data_storage_factory::create(0, t);
        assert(nullptr != temp_data);
        temp_data->load(ar);
        data_storage_factory::copy_core_data_from_src_to_dest(temp_data, m_data);
        delete temp_data;
    } else {
        m_data->load(ar);
    }
}

template <class A>
void graph::serialize(A& ar, const unsigned version)
{
    boost::serialization::split_member(ar, *this, version);
}

}

BOOST_CLASS_VERSION(graph_types::graph, 0)
