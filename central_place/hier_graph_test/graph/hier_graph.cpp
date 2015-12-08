/**
 * @file graph/hier_graph.cpp
 * @brief definition of hier_graph class.
 */

#include "hier_graph.h"
#include "hnode.h"
#include "child_hnode_iterator.h"
#include <assert.h>

hnode_collection_iterator hier_graph::get_level_iterator(const unsigned l) const
{
    assert(l < m_level_to_nodes.size());
    return hnode_collection_iterator(m_level_to_nodes[l]);
}

hnode* hier_graph::get_node(const unsigned l, const unsigned p_l) const
{
    assert(l < m_level_to_nodes.size());
    auto& l_nodes = m_level_to_nodes[l];
    assert(p_l < l_nodes.size());
    return l_nodes[p_l];
}

hnode* hier_graph::get_root() const
{
    return m_root;
}

void hier_graph::fill_level_to_nodes_collection(hnode* n)
{
    assert(nullptr != n);
    m_level_to_nodes[n->get_level()].push_back(n);
    hnode* child = nullptr;
    child_hnode_iterator it(n);
    while (nullptr != (child = it.next())) {
        fill_level_to_nodes_collection(child);
    }
}

hier_graph::hier_graph(const unsigned d, const unsigned l)
    : m_level_to_nodes(d - 1),
    m_root(new hnode(nullptr, l, d - 2, 0)),
    m_depth(d)
{
    assert(0 != l);
    assert(2 <= d);
    fill_level_to_nodes_collection(m_root);
}

hier_graph::~hier_graph()
{
    delete m_root;
}
