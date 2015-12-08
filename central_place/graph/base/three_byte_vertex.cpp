/**
 * @file base/three_byte_vertex.cpp
 * @brief definition of class three_byte_vertex.
 */

#include "three_byte_vertex.h"
#include "constants.h"
#include <assert.h>

namespace graph_types
{

three_byte_vertex& three_byte_vertex::operator=(const three_byte_vertex& other)
{
    m_value = other.m_value;
    return *this;
}

three_byte_vertex& three_byte_vertex::operator=(three_byte_vertex&& other)
{
    m_value = other.m_value;
    return *this;
}

three_byte_vertex& three_byte_vertex::operator=(const uint32_t& v)
{
    assert(v <= constants::UP_LIMIT_OF_VERTEX_VALUE);
    m_value = v;
    return *this;
}

three_byte_vertex::operator uint32_t() const
{
    return m_value;
}

three_byte_vertex::operator uint64_t() const
{
    return m_value;
}

three_byte_vertex& three_byte_vertex::operator+=(const three_byte_vertex& rv)
{
    m_value += rv.m_value;
    return *this;
}

three_byte_vertex& three_byte_vertex::operator-=(const three_byte_vertex& rv)
{
    m_value -= rv.m_value;
    return *this;
}

three_byte_vertex& three_byte_vertex::operator*=(const three_byte_vertex& rv)
{
    m_value *= rv.m_value;
    return *this;
}

three_byte_vertex& three_byte_vertex::operator/=(const three_byte_vertex& rv)
{
    m_value /= rv.m_value;
    return *this;
}

three_byte_vertex& three_byte_vertex::operator%=(const three_byte_vertex& rv)
{
    m_value %= rv.m_value;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const three_byte_vertex& v)
{
    os << v.m_value;
    return os;
}

std::istream& operator>>(std::istream& is, three_byte_vertex& v)
{
    uint32_t temp;
    is >> temp;
    assert(temp <= constants::UP_LIMIT_OF_VERTEX_VALUE);
    v.m_value = temp;
    return is;
}

bool three_byte_vertex::operator==(const three_byte_vertex& rv) const
{
    return m_value == rv.m_value;
}

bool three_byte_vertex::operator!=(const three_byte_vertex& rv) const
{
    return m_value != rv.m_value;
}

bool three_byte_vertex::operator<(const three_byte_vertex& rv) const
{
    return m_value < rv.m_value;
}

bool three_byte_vertex::operator>(const three_byte_vertex& rv) const
{
    return m_value > rv.m_value;
}

bool three_byte_vertex::operator<=(const three_byte_vertex& rv) const
{
    return m_value <= rv.m_value;
}

bool three_byte_vertex::operator>=(const three_byte_vertex& rv) const
{
    return m_value >= rv.m_value;
}

three_byte_vertex three_byte_vertex::operator+(const three_byte_vertex& rv) const
{
    return three_byte_vertex(m_value + rv.m_value);
}

three_byte_vertex three_byte_vertex::operator-(const three_byte_vertex& rv) const
{
    return three_byte_vertex(m_value - rv.m_value);
}

three_byte_vertex three_byte_vertex::operator*(const three_byte_vertex& rv) const
{
    return three_byte_vertex(m_value * rv.m_value);
}

three_byte_vertex three_byte_vertex::operator/(const three_byte_vertex& rv) const
{
    return three_byte_vertex(m_value / rv.m_value);
}

three_byte_vertex three_byte_vertex::operator%(const three_byte_vertex& rv) const
{
    return three_byte_vertex(m_value % rv.m_value);
}

three_byte_vertex& three_byte_vertex::operator++()
{
    ++m_value;
    return *this;
}

three_byte_vertex three_byte_vertex::operator++(int)
{
    three_byte_vertex temp(m_value++);
    return temp;
}

three_byte_vertex& three_byte_vertex::operator--()
{
    --m_value;
    return *this;
}

three_byte_vertex three_byte_vertex::operator--(int)
{
    three_byte_vertex temp(m_value--);
    return temp;
}

three_byte_vertex::three_byte_vertex() :
    m_value(0)
{}

three_byte_vertex::three_byte_vertex(const uint32_t v) :
    m_value(v)
{
    assert(v <= constants::UP_LIMIT_OF_VERTEX_VALUE);
}

three_byte_vertex::three_byte_vertex(const three_byte_vertex& other) :
    m_value(other.m_value)
{}

three_byte_vertex::three_byte_vertex(three_byte_vertex&& other) :
    m_value(other.m_value)
{}

}
