/**
 * @file randomizers/randomizator_base.cpp
 * @brief definition of class randomizator_base
 */

#include "randomizator_base.h"

randomizator_base::randomizator_base(graph_types::graph& graph,
    graph_types::sequent_null_edges& non_existing_edges) :
    m_random_generator(time(0)),
    m_graph(graph),
    m_non_existing_edges(non_existing_edges)
{}
