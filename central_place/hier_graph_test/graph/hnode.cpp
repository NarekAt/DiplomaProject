/**
 * @file graph/hnode.cpp 
 * @brief definition of hnode class.
 */

#include "hnode.h"
#include <assert.h>

hnode* hnode::get_parent() const
{
    return m_parent;
}

unsigned hnode::get_level() const
{
    return m_level;
}

unsigned hnode::get_place_in_level() const
{
    return m_place_in_level;
}

hnode* hnode::get_child(size_t i) const
{
    return m_children[i];
}

bool hnode::operator[](size_t i)
{
    assert(i < m_length);
    return m_connections[i];
}

void hnode::set(size_t i)
{
    assert(i < m_length);
    m_connections.set(i);
}

void hnode::unset(size_t i)
{
    assert(i < m_length);
    m_connections.reset(i);
}

void hnode::filp(size_t i)
{
    assert(i < m_length);
    m_connections.flip(i);
}

void hnode::flip()
{
    m_connections.flip();
}

hnode::hnode(hnode* p, const unsigned length, const unsigned l, const unsigned p_l)
    : m_parent(p),
    m_length(length),
    m_level(l),
    m_place_in_level(p_l),
    m_connections(length)
{
    assert(0 != length);
    if (nullptr == p) {
        assert(0 == p_l);
    }
    if (0 == l) {
        return;
    }
    for (int i = 0; i < m_length; ++i) {
        m_children.push_back(new hnode(this, m_length, l - 1, p_l * m_length + i));
    }
}

hnode::hnode(const hnode& o)
    : m_parent(o.m_parent),
    m_length(o.m_length),
    m_level(o.m_level),
    m_place_in_level(o.m_place_in_level),
    m_connections(o.m_length)
{
    for (int i = 0; i < m_connections.size(); ++i) {
        m_connections[i] = o.m_connections[i];
    }
    for (auto v : o.m_children) {
        m_children.push_back(new hnode(*v));
    }
}

hnode::~hnode()
{
    for (auto& c : m_children) {
        delete c;
    }
}
