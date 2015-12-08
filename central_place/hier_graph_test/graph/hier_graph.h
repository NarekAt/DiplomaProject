/**
 * @file graph/hier_graph.h 
 * @brief delcaration of hier_graph class.
 */

#pragma once

class hnode;
#include "hnode_collection_iterator.h"
#include <vector>

/**
 * @class hier_graph
 * @brief Facade on hierarchical graph data.
 */
class hier_graph
{    
public:
    /**
     * @brief Gets level node iterator.
     * @param l Level of graph.
     * @pre Level must be valid.
     */
    hnode_collection_iterator get_level_iterator(const unsigned l) const;

public:
    /**
     * @brief Gets node of hierarchical graph in given level and
     *        in given place.
     * @param l Level of node.
     * @param p_l Place in Level of node.
     * @pre level and place_in_level numbers must be valid for the graph.
     */
    hnode* get_node(const unsigned l, const unsigned p_l) const;

public:
    /**
     * @brief Gets root node of graph.
     */
    hnode* get_root() const;

private:
    void fill_level_to_nodes_collection(hnode* n);

public:
    /**
     * @brief Constructor.
     * @param d Depth of the tree.
     * @pre Depth must be >= 2.
     * @param l Length of children
     */
    hier_graph(const unsigned d, const unsigned l);

public:
    /**
     * @brief Destructor.
     */
    ~hier_graph();

private:
    typedef std::vector<std::vector<hnode*>> level_to_nodes_collection;

private:
    level_to_nodes_collection m_level_to_nodes;
    hnode* const m_root;
    const unsigned m_depth;
};
