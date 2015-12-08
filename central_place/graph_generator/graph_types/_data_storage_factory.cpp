/**
 * @file graph_types/_data_storage_factory.cpp
 * @brief Definition of data_storage_factory class.
 */

#include "_data_storage_factory.h"
#include "_graph_data_storage_bitsets_full.h"
#include "_graph_data_storage_bitsets_partial.h"
#include "_graph_data_storage_sorted_vectors_full.h"
#include "_graph_data_storage_sorted_vectors_partial.h"
#include "graph_constants.h"
#include <map>
#include <functional>
#include <assert.h>

namespace graph_types
{

namespace {

typedef std::map<const storage_core_type, std::function<
    graph_data_storage_base* (const graph_size s)>> type_to_create_data_storage;

static type_to_create_data_storage s_type_to_create_data_storage = {
    std::make_pair(storage_core_type::BITSETS_FULL, [] (const graph_size s) ->
        graph_data_storage_base* {
            return new graph_data_storage_bitsets_full(s);
        }),
    std::make_pair(storage_core_type::BITSETS_PARTIAL, [] (const graph_size s) ->
        graph_data_storage_base* {
            return new graph_data_storage_bitsets_partial(s);
        }),
    std::make_pair(storage_core_type::SORTED_VECTORS_FULL, [] (const graph_size s) ->
        graph_data_storage_base* {
            return new graph_data_storage_sorted_vectors_full(s);
        }),
    std::make_pair(storage_core_type::SORTED_VECTORS_PARTIAL, [] (const graph_size s) ->
        graph_data_storage_base* {
            return new graph_data_storage_sorted_vectors_partial(s);
        }),
    std::make_pair(storage_core_type::AUTODETECT, [] (const graph_size s) ->
        graph_data_storage_base* {
            assert(!"AUTODETECT should not be used in this map");
        })
};

}

graph_data_storage_base* data_storage_factory::create(
    const graph_size s, const storage_core_type t)
{
    auto it = s_type_to_create_data_storage.find(t);
    assert(s_type_to_create_data_storage.end() != it);
    return (it->second)(s);
}

graph_data_storage_base* data_storage_factory::create(
    const graph_size s, const double p)
{
    /**
     * @note for now in any case we are creating and returning
     *       full bitset core data, as the most optimal in performance and
     *       in memory aspects.
     */
    auto it = s_type_to_create_data_storage.find(storage_core_type::BITSETS_FULL);
    assert(s_type_to_create_data_storage.end() != it);
    return (it->second)(s);
}

namespace {

typedef std::map<const storage_core_type, std::function<
    void (const graph_data_storage_base* src,
        graph_data_storage_base* dest)>> type_to_copy_data_storage;

static type_to_copy_data_storage s_type_to_copy_data_storage = {
    std::make_pair(storage_core_type::BITSETS_FULL, [] (
        const graph_data_storage_base* src,graph_data_storage_base* dest) {
            auto true_type_src = dynamic_cast<
                const  graph_data_storage_bitsets_full*>(src);
            assert(nullptr != true_type_src);
            auto true_type_dest = dynamic_cast<
                graph_data_storage_bitsets_full*>(dest);
            assert(nullptr != true_type_dest);
            *true_type_dest = *true_type_src;
        }),
    std::make_pair(storage_core_type::BITSETS_PARTIAL, [] (
        const graph_data_storage_base* src,graph_data_storage_base* dest) {
            auto true_type_src = dynamic_cast<
                const graph_data_storage_bitsets_partial*>(src);
            assert(nullptr != true_type_src);
            auto true_type_dest = dynamic_cast<
                graph_data_storage_bitsets_partial*>(dest);
            assert(nullptr != true_type_dest);
            *true_type_dest = *true_type_src;
        }),
    std::make_pair(storage_core_type::SORTED_VECTORS_FULL, [] (
        const graph_data_storage_base* src,graph_data_storage_base* dest) {
            auto true_type_src = dynamic_cast<
                const graph_data_storage_sorted_vectors_full*>(src);
            assert(nullptr != true_type_src);
            auto true_type_dest = dynamic_cast<
                graph_data_storage_sorted_vectors_full*>(dest);
            assert(nullptr != true_type_dest);
            *true_type_dest = *true_type_src;
        }),
    std::make_pair(storage_core_type::SORTED_VECTORS_PARTIAL, [] (
        const graph_data_storage_base* src,graph_data_storage_base* dest) {
            auto true_type_src = dynamic_cast<
                const graph_data_storage_sorted_vectors_partial*>(src);
            assert(nullptr != true_type_src);
            auto true_type_dest = dynamic_cast<
                graph_data_storage_sorted_vectors_partial*>(dest);
            assert(nullptr != true_type_dest);
            *true_type_dest = *true_type_src;
        }),
    std::make_pair(storage_core_type::AUTODETECT, [] (
        const graph_data_storage_base* src,graph_data_storage_base* dest) {
            assert(!"AUTODETECT should not be used in this map");
        })
};

void copy_edges_of_core_data(
    const graph_data_storage_base* src, graph_data_storage_base* dest)
{
    assert(nullptr != src);
    assert(nullptr != dest);
    const auto size_of_src = src->size();
    assert(size_of_src == dest->size());
    vertex next_vertex = constants::VERTEX_0;
    for (; next_vertex != size_of_src; ++next_vertex) {
        const auto next_edges = src->neighbor_edges_sequence(next_vertex);
        for (auto e : next_edges) {
            dest->add_edge_if_does_not_exist(e);
        }
    }
}

}

void data_storage_factory::copy_core_data_from_src_to_dest(
    const graph_data_storage_base* src, graph_data_storage_base* dest)
{
    assert(nullptr != src);
    assert(nullptr != dest);
    const auto type_of_src = src->core_type();
    const auto type_of_dest = dest->core_type();
    const auto size_of_src = src->size();
    dest->reset(size_of_src);
    if (type_of_src == type_of_dest) {
        auto it = s_type_to_copy_data_storage.find(type_of_src);
        assert(s_type_to_copy_data_storage.end() != it);
        (it->second)(src, dest);
    } else {
        copy_edges_of_core_data(src, dest);
    }
}

graph_data_storage_base* data_storage_factory::create_core_data_copy_from_src(
    const graph_data_storage_base* src)
{
    assert(nullptr != src);
    auto dest = create(src->size(), src->core_type());
    copy_core_data_from_src_to_dest(src, dest);
    return dest;
}

}
