/**
 * @file property_counters/property_counter_factory.h
 * @brief declaration of property_counter_factory class
 */

#pragma once

#include "graph_types.h"
#include "property_counter_base.h"

/**
 * @class property_counter_factory
 * @brief creater of property_counters.
 */
class property_counter_factory
{
public:
    /**
     * @brief Creates and gets property counter
     *        by given alternate_property_type.
     * @param graph Graph for property counter.
     * @param t Property counter type
     * @note Got pointer must be deleted after use.
     */
    static property_counter_base* get_counter(
        graph_types::graph& graph,
        alternate_property_type t);
};
