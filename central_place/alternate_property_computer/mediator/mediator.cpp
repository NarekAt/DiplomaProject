/**
 * @file mediator/mediator.cpp
 * @brief definition of class mediator.
 */

#include "mediator.h"
#include "erdos_renyi_reader.h"

//task managers
#include "single_process_task_manager.h"
#include "main_process_task_manager.h"
#include "secondary_process_task_manager.h"
#include "graph_item_property_task_manager.h"

#include <iostream>
#include <ctime>
#include <chrono>
#include <boost/filesystem.hpp>
#include <assert.h>

mediator* mediator::s_instance = nullptr;

void mediator::init(const arg_name_to_value_map& a_n_v)
{
    assert(!m_inited);
    m_inited = true;
    // if argument list is empty
    // it means that this is secondary process.
    if (a_n_v.empty()) {
        return;
    }
    try {
        auto gr_it = a_n_v.find("graph_file");
        assert(a_n_v.end() != gr_it);
        m_graphPaths.push_back(boost::any_cast<std::string>(gr_it->second));

        auto apt_it = a_n_v.find("alternate_property_types");
        assert(a_n_v.end() != apt_it);
        m_alternate_property_types = boost::any_cast<
            apt_list>(apt_it->second);

        m_non_item_relateds_count = std::count_if( m_alternate_property_types.begin(), m_alternate_property_types.end(),
                [](const alternate_property_type& a){ return !is_graph_item_related_property(a); } );

        if (0 == m_non_item_relateds_count)
            return;

        assert(m_non_item_relateds_count == 1);

        auto mu_it = a_n_v.find("mu_file");
        assert(a_n_v.end() != mu_it);

        erdos_renyi_reader r;
        r.get_mus_from_file(
            boost::any_cast<std::string>(mu_it->second), m_mu_list);
        
        auto sc_it = a_n_v.find("step_count");
        assert(a_n_v.end() != sc_it);
        m_step_count = boost::any_cast<unsigned>(sc_it->second);

        auto rt_it = a_n_v.find("randomization_type");
        assert(a_n_v.end() != rt_it);
        m_randomization_type = boost::any_cast<randomization_type>(
            rt_it->second);
        assert(INVALID_RT != m_randomization_type);

    } catch (const boost::bad_any_cast&) {
        assert(!"bad any cast");
    }
}

void
mediator::init(const CFGParser::Config& config)
{
    assert(!m_inited);
    m_inited = true;

    m_graphPaths = config.gpList;
    m_calc_distr = config.calculateDistr;
    m_calc_avg = config.calculateAvg;
    m_alternate_property_types = config.aptList;
}

void mediator::run_item_prop_task_mgr(boost::mpi::communicator& world)
{
    std::string dirPrefix = "_graph_" + std::to_string(world.rank());
    results_writer::get_instance().prapare_writer(m_vertex_count, m_probability, dirPrefix);

    erdos_renyi_reader r;
    graph_types::graph graph (graph_types::storage_core_type::BITSETS_FULL);

    assert(world.size() == m_graphPaths.size());
    r.get_graph_and_properties_from_file(m_graphPaths[world.rank()],
    graph, m_vertex_count, m_probability);

    graph_item_property_task_manager t_m(graph,
    m_alternate_property_types, m_calc_distr, m_logger);
    t_m.run();
}

void mediator::run_global_prop_task_mgr(boost::mpi::communicator& world)
{
    if (1 == world.size()) {
        single_process_task_manager t_m(world, m_logger);
        run_task_manager_and_send_to_output(t_m);
        m_logger.close();
    } else {
        if (0 == world.rank()) {
            main_process_task_manager t_m(world, m_logger);
            run_task_manager_and_send_to_output(t_m);
            m_logger.close();
        } else {
            secondary_process_task_manager t_m(world, m_logger);
            t_m.run();
        }
    }
}

void mediator::run(boost::mpi::communicator& world)
{
    assert(m_inited);

    if(m_non_item_relateds_count == 0)
    {
        run_item_prop_task_mgr(world);
    }
    else
        run_global_prop_task_mgr(world);
}

void mediator::write_results(const single_results_list& s_r, double mu) const
{
    results_writer::get_instance().write_single_results_list(s_r, mu);
}

void mediator::run_task_manager_and_send_to_output(
    task_manager_base& t_m)
{
    results_writer::get_instance().prapare_writer(m_vertex_count, m_probability);

    assert(1 == m_alternate_property_types.size());
    time_t c_t = time(0);

    graph_types::graph graph(graph_types::storage_core_type::BITSETS_FULL);
    erdos_renyi_reader r;
    r.get_graph_and_properties_from_file(m_graphPaths.front(),
                                         graph, m_vertex_count, m_probability);

    m_logger << "\n>>>>> Calculation Started: " << ctime(&c_t);
    t_m.init(graph, m_mu_list, m_step_count, 
        m_randomization_type, m_alternate_property_types.back());

    t_m.run();
    c_t = time(0);
    m_logger << "\n>>>>> Calculation Finished: " << ctime(&c_t);
}

mediator& mediator::get_instance()
{
    assert(s_instance != nullptr);
    return *s_instance;
}

void mediator::instantiate(std::ofstream& logger)
{
    assert(s_instance == nullptr);
    s_instance = new mediator(logger);
}

void mediator::destroy()
{
    assert(s_instance != nullptr);
    delete s_instance;
    s_instance = nullptr;
}

mediator::mediator(std::ofstream& logger) :
    m_inited(false),
    m_logger(logger)
{}
