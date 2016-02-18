/**
 * @file task_managers/graph_item_property_task_manager.h
 * @brief declaration of graph_item_property_task_manager class.
 */

#pragma once

#include "types.h"
#include "graph_types.h"
#include "graph.h"
#include "igraph_task_manager.h"

#include "utility.h"

class graph_item_property_task_manager : public igraph_task_manager
{
public:
    DECLARE_DELEGATING_CTOR3(graph_item_property_task_manager, igraph_task_manager);

    void run();
};

