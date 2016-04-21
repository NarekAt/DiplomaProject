#include "graph_item_property_task_manager.h"
#include "property_computer_factory.h"
#include "property_computers.h"

#include "mediator.h"

graph_item_property_task_manager::graph_item_property_task_manager(const graph_types::graph& g,
                                                                   const apt_list& apts,
                                                                   bool calcDistr,
                                                                   std::ofstream& logger)
        : igraph_task_manager(g, INVALID_APT, logger)
        , m_graph_item_related_apts(apts)
        , m_calc_distr(calcDistr)
{
    Base::PropertyComputerController::getInstance().registerPropertyComputers();
}

void
graph_item_property_task_manager::run()
{
    for (const alternate_property_type& type : m_graph_item_related_apts)
    {
        Base::PropertyComputerRunner::compute_and_write(m_initial_graph, type);
        if (m_calc_distr)
            Base::PropertyComputerRunner::calculate_distributions_and_write(m_initial_graph, type);
    }
}

graph_item_property_task_manager::~graph_item_property_task_manager()
{
    m_logger.close();
}
