#pragma once

/**
 * @file base/_boost_dynamic_bitset_serialization.h
 * @brief Declaration of boost dynamic_bitset serialization.
 */

#include <cstddef>

#include <boost/config.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/serialization/vector.hpp>

namespace boost {

namespace serialization {

template <class Archive, typename Block, typename Allocator>
inline void save(Archive& ar, boost::dynamic_bitset<Block, Allocator> const& t,
    const unsigned int version)
{
    std::size_t size = t.size();
    ar << size;
    std::vector<Block> v(t.num_blocks());
    to_block_range(t, v.begin());
    ar & v;
}

template <class Archive, typename Block, typename Allocator>
inline void load(Archive& ar, boost::dynamic_bitset<Block, Allocator>& t,
    const unsigned int version)
{
    std::size_t size;
    ar & size;
    t.resize(size);
    std::vector<Block> v;
    ar & v;
    from_block_range(v.begin(), v.end(), t);
}

template <class Archive, typename Block, typename Allocator>
inline void serialize(Archive& ar, boost::dynamic_bitset<Block, Allocator>& t,
    const unsigned int version)
{
    boost::serialization::split_free(ar, t, version);
}

}

}
