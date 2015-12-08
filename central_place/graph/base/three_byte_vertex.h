#pragma once

/**
 * @file base/three_byte_vertex.h
 * @brief declaration of class three_byte_vertex.
 */

#include <stdint.h>
#include <iostream>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <type_traits>

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
 * @class three_byte_vertex
 * @brief represents vertex of the graph
 * @note This type is needed for storing index of vertex
 *       in 3 bytes: Index range of vertices is [0, 16777216].
 * @note Added restriction to interact with three_byte_vertex
 *       only with uint32_t standart type.
 */
class three_byte_vertex
{
    /// @name Assignment Operators.
    /// @{
public:
    /**
     * @brief Assignment operator.
     * @param other Right place three_byte_vertex of assignment.
     */
    three_byte_vertex& operator=(const three_byte_vertex& other);
    
    /**
     * @brief Move assignment operator.
     * @param other Right place three_byte_vertex for move.
     */
    three_byte_vertex& operator=(three_byte_vertex&& other);

    /**
     * @brief Assignment operator.
     * @param v Right place uint32_t value of assignment.
     */
    three_byte_vertex& operator=(const uint32_t& v);
    /// @}

    /// @name Casting operators.
    /// @{
public:
    /**
     * @brief uint32_t casting operator.
     */
    operator uint32_t() const;

    /**
     * @brief unit64_t casting operator.
     */
    operator uint64_t() const;
    /// @}

    /// @name Compund Assignment Operators.
    /// @{
public:
    /**
     * @brief Compound addition assignment operator.
     * @param rv Right side three_byte_vertex for compound operation.
     */
    three_byte_vertex& operator+=(const three_byte_vertex& rv);

    /**
     * @brief Compound subtraction assignment operator.
     * @param rv Right side three_byte_vertex for compound operation.
     */
    three_byte_vertex& operator-=(const three_byte_vertex& rv);
    
    /**
     * @brief Compound multiplication assignment operator.
     * @param rv Right side three_byte_vertex for compound operation.
     */
    three_byte_vertex& operator*=(const three_byte_vertex& rv);

    /**
     * @brief Compound division assignment operator.
     * @param rv Right side three_byte_vertex for compound operation.
     */
    three_byte_vertex& operator/=(const three_byte_vertex& rv);

    /**
     * @brief Compound modulo assignment operator.
     * @param rv Right side three_byte_vertex for compound operation.
     */
    three_byte_vertex& operator%=(const three_byte_vertex& rv);
    /// @}

    /// @name Input and Output Operators.
    /// @{
public:
    /**
     * @brief Output operator.
     * @param os Output stream.
     * @param v three_byte_vertex for sending to stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const three_byte_vertex& v);

    /**
     * @brief Input operator.
     * @param is Input stream.
     * @param v three_byte_vertex for storing date from stream.
     */
    friend std::istream& operator>>(std::istream& is, three_byte_vertex& v);
    /// @}
    
    /// @name Copmarison operators
    /// @{
public:
    /**
     * @brief Equal to operator.
     * @param rv Right side three_byte_vertex for comparision.
     */
    bool operator==(const three_byte_vertex& rv) const;
    
    /**
     * @brief Not Equal to operator.
     * @param rv Right side three_byte_vertex for comparision.
     */
    bool operator!=(const three_byte_vertex& rv) const;
    
    /**
     * @brief Less than operator.
     * @param rv Right side three_byte_vertex for comparision.
     */
    bool operator<(const three_byte_vertex& rv) const;

    /**
     * @brief Greater than  operator.
     * @param rv Right side three_byte_vertex for comparision.
     */
    bool operator>(const three_byte_vertex& rv) const;

    /**
     * @brief Less than or equal to operator.
     * @param rv Right side three_byte_vertex for comparision.
     */
    bool operator<=(const three_byte_vertex& rv) const;

    /**
     * @brief Greater than or equal to operator.
     * @param rv Right side three_byte_vertex for comparision.
     */
    bool operator>=(const three_byte_vertex& rv) const;
    /// @{

    /// @name Arithmetic Operators.
    /// @{
public:
    /**
     * @brief Addition operator.
     * @param rv Right side three_byte_vertex for arithmetic operation.
     */
    three_byte_vertex operator+(const three_byte_vertex& rv) const;

    /**
     * @brief subtraction operator.
     * @param rv Right side three_byte_vertex for arithmetic operation.
     */
    three_byte_vertex operator-(const three_byte_vertex& rv) const;

    /**
     * @brief multiplication operator.
     * @param rv Right side three_byte_vertex for arithmetic operation.
     */
    three_byte_vertex operator*(const three_byte_vertex& rv) const;

    /**
     * @brief division operator.
     * @param rv Right side three_byte_vertex for arithmetic operation.
     */
    three_byte_vertex operator/(const three_byte_vertex& rv) const;

    /**
     * @brief modulo operator.
     * @param rv Right side three_byte_vertex for arithmetic operation.
     */
    three_byte_vertex operator%(const three_byte_vertex& rv) const;
    /// @}

    /// @name Increment and decrement operators.
    /// @{
public:
    /**
     * @brief Prefix increment operator.
     */
    three_byte_vertex& operator++();

    /**
     * @brief Postfix increment operator.
     */
    three_byte_vertex operator++(int);

    /**
     * @brief Prefix decrement operator.
     */
    three_byte_vertex& operator--();

    /**
     * @brief Postfix decrement operator.
     */
    three_byte_vertex operator--(int);
    /// @}

    /// @name Constructors.
    /// @{
public:
    /**
     * @brief Default Constructor.
     */
    three_byte_vertex();

    /**
     * @brief Constructor.
     * @param v index of three_byte_vertex.
     * @note We are not passing value by reference
     *       because it can take more then 4 bytes place
     *       depending on OS type (32bit or 64bit).
     */
    three_byte_vertex(const uint32_t v);

    /**
     * @brief Copy-Constructor.
     * @param other Other three_byte_vertex for copy construction.
     */
    three_byte_vertex(const three_byte_vertex& other);

    /**
     * @brief Move Constructor.
     * @param other three_byte_vertex to move.
     */
    three_byte_vertex(three_byte_vertex&& other);
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
    uint32_t m_value : 24;
} __attribute__((packed));

template <class A>
void three_byte_vertex::save(A& ar, const unsigned int version) const
{
    static_assert(std::is_same<A, boost::archive::text_oarchive>::value ||
        std::is_same<A, boost::archive::binary_oarchive>::value ||
        std::is_same<A, boost::mpi::packed_oarchive>::value,
        "archive type should be text_oarchive or binary_oarchive");
    uint32_t temp = m_value;
    ar << temp;
}

template <class A>
void three_byte_vertex::load(A& ar, const unsigned version)
{
    static_assert(std::is_same<A, boost::archive::text_iarchive>::value ||
        std::is_same<A, boost::archive::binary_iarchive>::value ||
        std::is_same<A, boost::mpi::packed_iarchive>::value,
        "archive type should be text_iarchive or binary_iarchive");
    uint32_t temp = m_value;
    ar >> temp;
    m_value = temp;
}

template <class A>
void three_byte_vertex::serialize(A& ar, const unsigned version)
{
    boost::serialization::split_member(ar, *this, version);
}

}

BOOST_CLASS_VERSION(graph_types::three_byte_vertex, 0)
