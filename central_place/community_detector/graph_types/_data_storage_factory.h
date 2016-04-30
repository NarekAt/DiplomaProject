#pragma once

/**
 * @file graph_types/_data_storage_factory.h
 * @brief Declaration of data_storage_factory class.
 */

#include "graph_types.h"

namespace graph_types
{

class graph_data_storage_base;

/**
 * @class data_storage_factory
 * @brief Factory class for creation graph's data storage.
 */
class data_storage_factory
{
    /// @name Creating interface.
    /// @{
public:
    /**
     * @brief Creates and gets data storage of graph.
     * @param s Vertices count.
     * @param t Type of data storage.
     * @note Got pointer must be deleted after use.
     */
    static graph_data_storage_base* create(const graph_size s, const storage_core_type t);

    /**
     * @brief Creates and gets data strage of graph
     *        by autodetection depending on vertices count
     *        and existance probability of edge.
     * @param s Vertices count.
     * @param p Existance probability of edge.
     * @pre p must be in range [0.0, 1.0].
     */
    static graph_data_storage_base* create(const graph_size s, const double p);
    /// @}

    /// @name Copying interface.
    /// @{
public:
    /**
     * @brief Copy core data of graph from source to destination.
     * @param src Source core data.
     * @param dest Destination core data.
     */
    static void copy_core_data_from_src_to_dest(const graph_data_storage_base* src,
        graph_data_storage_base* dest);

    /**
     * @brief Create copy of core data from source
     * @param src Source core data.
     */
    static graph_data_storage_base* create_core_data_copy_from_src(
        const graph_data_storage_base* src);
    /// @}
};

}
