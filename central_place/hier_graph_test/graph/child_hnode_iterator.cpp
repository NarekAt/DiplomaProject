/**
 * @file graph/child_hnode_iterator.cpp
 * @brief definition of child_hnode_iterator class.
 */

#include "child_hnode_iterator.h"
#include "hnode.h"

void child_hnode_iterator::reset()
{
    m_index = 0;
}

hnode* child_hnode_iterator::next()
{
    if (m_index == m_children.size()) {
        return nullptr;
    }
    return m_children[m_index++];
}

child_hnode_iterator::child_hnode_iterator(hnode* p)
    : m_children(p->m_children),
    m_index(0)
{}
