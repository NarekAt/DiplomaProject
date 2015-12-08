/**
 * @file graph/child_hnode_iterator.h 
 * @brief delcaration of child_hnode_iterator class.
 */

#pragma once

class hnode;
#include <vector>

/**
 * @class child_hnode_iterator.
 * @brief Iterator on childrent of node.
 */
class child_hnode_iterator
{
public:
    /**
     * @brief Resets iterator.
     */
    void reset();

public:
    /**
     * @brief Gets next child node.
     * @note if iteration reached end, returns nullptr.
     */
    hnode* next();

public:
    /**
     * @brief Constructor.
     * @param p Parent of children.
     */
    child_hnode_iterator(hnode* p);

private:
    const std::vector<hnode*>& m_children;
    unsigned m_index;
};
