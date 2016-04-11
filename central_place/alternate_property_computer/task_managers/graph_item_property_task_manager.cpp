#include "graph_item_property_task_manager.h"
#include "betweenness_centrality.h"
#include "connected_components.h"
#include "degree_computer.h"
#include "eigen_values.h"
#include "shortestpath.h"

#include "mediator.h"

void
graph_item_property_task_manager::run()
{
    for (const auto& type : m_graph_item_related_apts)
    {
       switch(type)
       {
           case CONNECTED_COMPONENTS:
           {
           		Base::ConnectedComponents cp (m_initial_graph);
           		cp.compute();
           		mediator::get_instance().write_results(cp.getResult(), CONNECTED_COMPONENTS);
                break;
           }
           case SHORTEST_PATH:
           {
                Base::ShortestPath sp (m_initial_graph);
                sp.compute();
                mediator::get_instance().write_results(sp.getResult(), SHORTEST_PATH);
                break;
           }
           case BETWEENNESS_CENTRALITY:
           {
                Base::BC bc (m_initial_graph);
                bc.compute();
                mediator::get_instance().write_results(bc.getResult(), BETWEENNESS_CENTRALITY);
                break;
           }
           case EIGEN_VALUES:
           {
                Base::EigenValues ev (m_initial_graph);
                ev.compute();
                mediator::get_instance().write_results(ev.getResult(), EIGEN_VALUES);
                break;
           }
           case DEGREE:
           {
                Base::DegreeComputer dc (m_initial_graph);
                dc.compute();
                mediator::get_instance().write_results(dc.getResult(), DEGREE);
                break;
           }
           default:
           {
                // TODO: throw exception
                assert(false);
           }
       }
    }
}


