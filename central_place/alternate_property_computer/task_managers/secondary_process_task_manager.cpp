/**
 * @file task_managers/secondary_process_task_manager.cpp
 * @brief definition of secondary_process_task_manager class.
 */

#include "secondary_process_task_manager.h"
#include "randomizator_base.h"
#include "property_counter_base.h"
#include <boost/serialization/utility.hpp>
#include <iostream>

void secondary_process_task_manager::run()
{
    bool am_i_needed = receive_ingredients();
    if (!am_i_needed) {
        return;
    }
    calculate_and_send();
}

void secondary_process_task_manager::treat_status_information(const persent_to_mu& info)
{
    assert(!m_status_tags.empty());
    m_status_requests.push_back(boost::mpi::request());
    m_status_cached_infos.push_back(info);
    m_status_requests.back() =
       m_world.isend(0, m_status_tags.front(), m_status_cached_infos.back());
    m_status_tags.erase(m_status_tags.begin());
}

bool secondary_process_task_manager::receive_ingredients()
{
    bool process_is_needed = false;
    m_world.recv(0, mpi_tag::PROCESS_IS_NEEDED, process_is_needed);
    if (!process_is_needed) {
        return false;
    }
    m_world.recv(0, GRAPH, m_initial_graph);
    m_world.recv(0, ALTERNATE_PROPERTY_INITIAL_COUNT,
        m_initial_property_count);
    m_world.recv(0, STEP_COUNT, m_step_count);
    m_world.recv(0, PASS_COUNT, m_pass_count);
    int r_type = 0;
    m_world.recv(0, RANDOMIZATION_TYPE, r_type);
    m_randomizator_type = static_cast<randomization_type>(r_type);
    int ap_type = 0;
    m_world.recv(0, ALTERNATE_PROPERTY_TYPE, ap_type);
    m_alternate_property_type = static_cast<alternate_property_type>(
        ap_type);
    m_world.recv(0, MUS, m_taged_mus);
    m_world.recv(0, STATUS_TAGS, m_status_tags);
    return true;
}

void secondary_process_task_manager::calculate_and_send()
{
    calculate_initial_non_existing_edges();
    std::vector<boost::mpi::request> requests;
    for (auto t_m : m_taged_mus) {
        m_results.push_back(std::make_pair(
            t_m.second, single_results_list()));
        auto& c_r = m_results.back();
        calculate_for_single_mu_by_pass_count(c_r.second, t_m.second);
        requests.push_back(boost::mpi::request());
        requests.back() = m_world.isend(0, t_m.first, c_r);
    }
    boost::mpi::wait_all(m_status_requests.begin(), m_status_requests.end());
    boost::mpi::wait_all(requests.begin(), requests.end());
}

secondary_process_task_manager::secondary_process_task_manager(
    boost::mpi::communicator& world, std::ofstream& logger) :
    task_manager_base(world, logger)
{}
