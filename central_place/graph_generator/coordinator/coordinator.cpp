/**
 * @file coordinator/coordinator.cpp
 * @brief definition of class coordinator.
 */

#include "coordinator.h"
#include "generator.h"
#include "writer.h"
#include <iostream>
#include <ctime>
#include <assert.h>

coordinator* coordinator::s_instance = nullptr;

void coordinator::init(const arg_name_to_value_map& a_n_v)
{
    assert(!m_inited);
    m_inited = true;
    try {
        auto v_c_it = a_n_v.find("size"); 
        assert(a_n_v.end() != v_c_it);
        m_vertex_count = boost::any_cast<unsigned>(v_c_it->second);
        auto p_it = a_n_v.find("probability");
        assert(a_n_v.end() != p_it);
        m_probability = boost::any_cast<double>(p_it->second);
        auto ct_it = a_n_v.find("core_type");
        assert(a_n_v.end() != ct_it);
        m_core_type = boost::any_cast<graph_types::storage_core_type>(ct_it->second);
        auto of_it = a_n_v.find("output_file");
        assert(a_n_v.end() != of_it);
        m_output_file = boost::any_cast<std::string>(of_it->second);
    } catch (const boost::bad_any_cast&) {
        assert(!"bad any cast");
    }
}

void coordinator::run()
{
    generator g;
    writer w;
    w.run(g.run(m_vertex_count, m_probability, m_core_type, m_logger),
        m_vertex_count, m_probability, m_output_file, m_logger);
    assert(m_inited);
}

coordinator& coordinator::get_instance()
{
    assert(s_instance != nullptr);
    return *s_instance;
}

void coordinator::instantiate(std::ofstream& logger)
{
    assert(s_instance == nullptr);
    s_instance = new coordinator(logger);
}

void coordinator::destroy()
{
    assert(s_instance != nullptr);
    delete s_instance;
    s_instance = nullptr;
}

coordinator::coordinator(std::ofstream& logger) :
    m_inited(false), m_logger(logger)
{}
