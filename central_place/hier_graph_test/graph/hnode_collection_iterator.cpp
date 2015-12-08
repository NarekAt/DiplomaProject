/**
 * @file graph/hnode_collection_iterator.cpp
 * @brief definition of hnode_collection_iterator class.
 */

#include "hnode_collection_iterator.h"
#include "hnode.h"

void hnode_collection_iterator::reset()
{
    m_index = 0;
}

hnode* hnode_collection_iterator::next()
{
    if (m_index == m_collection.size()) {
        return nullptr;
    }
    return m_collection[m_index++];
}

hnode_collection_iterator::hnode_collection_iterator(const hnode_collection& c)
    : m_collection(c),
    m_index(0)
{}
