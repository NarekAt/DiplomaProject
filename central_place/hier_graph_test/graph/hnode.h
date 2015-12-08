/**
 * @file graph/hnode.h 
 * @brief delcaration of hnode class.
 */

#pragma once

#include <vector>
#include <boost/dynamic_bitset.hpp>

/**
 * @class hnode
 * @brief represents node of hierarchical graph.
 */
class hnode
{
public:
    /**
     * @brief Gets parent of this node.
     */
    hnode* get_parent() const;

public:
    /**
     * @brief Gets level of this node.
     */
    unsigned get_level() const;

public:
    /**
     * @brief Gets place in level of this node.
     */
    unsigned get_place_in_level() const;

public:
    /**
     * @brief Gets Child with given index
     * @param i index of child.
     */
    hnode* get_child(size_t i) const;

public:
    /**
     * @brief access to connection with given index.
     * @param i index of connection.
     */
    bool operator[](size_t i);

public:
    /**
     * @brief Sets connection with given index.
     * @param i index of connection.
     */
    void set(size_t i);

public:
    /**
     * @brief Unsets connection with given index.
     * @param i index of connection.
     */
    void unset(size_t i);

public:
    /**
     * @brief Flips connection with given index.
     * @param i index of connection.
     */
    void filp(size_t i);

public:
    /**
     * @brief Flips all connections.
     */
    void flip();

private:
    /**
     * @brief Constructor.
     * @param p Parent of this node.
     * @param length Length of node (bitset)
     * @param l Level in graph.
     * @param p_l place in level of this node.
     */
    hnode(hnode* p, const unsigned length, const unsigned l, const unsigned p_l);

private:
    /**
     * @brief Copy constructor.
     * @param o Node to copy.
     */
    hnode(const hnode& o);

private:
    hnode& operator=(const hnode& o) = delete;

private:
    /**
     * @brief Destructor.
     */
    ~hnode();

private:
    hnode* m_parent;
    std::vector<hnode*> m_children;
    const unsigned m_length;
    const unsigned m_level;
    const unsigned m_place_in_level;
    boost::dynamic_bitset<> m_connections;

public:
    /**
     * @brief Made friend child_hnode_iterator to 
     *        give access to the m_children private class member.
     */
    friend class child_hnode_iterator;

    /**
     * @brief Made friend hier_graph to give access to the constructor
     *        and destructor, which are private.
     */
    friend class hier_graph;
};
