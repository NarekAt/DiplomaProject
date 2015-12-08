/**
 * @file task_managers/single_process_task_manager.cpp
 * @brief definition of single_process_task_manager class.
 */

#include "single_process_task_manager.h"
#include "property_counter_base.h"
#include "randomizator_factory.h"
#include "mediator.h"
#include <iostream>

void single_process_task_manager::run()
{
    assert(m_inited);
    for (auto& mu : m_mu_list) {
        single_results_list c_r;
        calculate_for_single_mu_by_pass_count(c_r, mu);
        mediator::get_instance().write_results(c_r, mu);
    }
}

void single_process_task_manager::treat_status_information(const persent_to_mu& info)
{
    // Means That whole calculation was done for came mu.
    if (0 == info.first) {
        m_logger << "\n*** Calculation was done for mu: " << info.second
            << " ***\n";
        m_logger.flush();
        return;
    }
    std::string p_t_n = get_alternate_property_name_by_type(
        m_counter->get_type());
    std::string info_message = std::string("calculation by ") + p_t_n + 
        std::string(" was done by ") + std::to_string(info.first) + 
        std::string("% for mu ") + std::to_string(info.second);
    m_logger << info_message << std::endl;
    m_logger.flush();
}

single_process_task_manager::single_process_task_manager(
    boost::mpi::communicator& world, std::ofstream& logger) :
    task_manager_base(world, logger)
{}
