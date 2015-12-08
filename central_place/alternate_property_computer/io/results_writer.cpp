/**
 * @file io/results_writer.cpp
 * @brief definition of results_writer class
 */

#include "results_writer.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

results_writer* results_writer::s_instance = nullptr;

void results_writer::prapare_writer(unsigned n, double p)
{
    m_vertex_count = n;
    m_probability = p;
    assert(!m_is_writer_ready);
    if (!prepare_output_directory()) {
        // TODO: throw exception.
        return; // dont forget to remove, 
                // after throw part will be implemented.
    }
    m_is_writer_ready = true;
}

namespace {

bool if_dir_dont_exists_then_create(const std::string& d_n)
{
    auto f = boost::filesystem::status(d_n);
    if (!boost::filesystem::exists(f)) {
        boost::filesystem::create_directory(d_n);
    } else if (!boost::filesystem::is_directory(f)) {
        return false;
    }
    return true;
}

std::string get_time_name_of_folder()
{
    auto tt = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    auto ptm = std::localtime(&tt);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y.%m.%d_%H.%M.%S", ptm);
    std::string name = std::string("results_") + std::string(buf);
    return name;
}

}

bool results_writer::prepare_output_directory()
{
    assert(!m_is_writer_ready);
    m_directory_name = "global_results";
    if (!if_dir_dont_exists_then_create(m_directory_name)) {
        return false;
    }
    m_directory_name += std::string("/") + 
        "alternate_property_computer_results";
    if (!if_dir_dont_exists_then_create(m_directory_name)) {
        return false;
    }
    m_directory_name += std::string("/") +
        get_time_name_of_folder() + "_N" + std::to_string(m_vertex_count) +
        "_p" + std::to_string(m_probability);
    if (!if_dir_dont_exists_then_create(m_directory_name)) {
        return false;
    }
    return true;
}

void results_writer::write_single_results_list(
    const single_results_list& r, double mu) const
{
    assert(m_is_writer_ready);
    std::string file_name = m_directory_name + "/" + 
        "mu" + std::to_string(mu) + ".txt";
    auto f = boost::filesystem::status(file_name);
    if (boost::filesystem::exists(f)) {
        if (!boost::filesystem::is_regular_file(f)) {
            // TODO: write error message.
            return;
        }
        // TODO: write info message.
        return;
    }
    std::ofstream output;
    output.open(file_name);
    if (!output.is_open()) {
        // TODO: write error message.
        return;
    }
    output << m_vertex_count << " " << m_probability << " " << mu << std::endl;
    for (auto n_r : r) {
        output << n_r.first << " " << n_r.second << std::endl;
    }
    output.close();
    // TODO: change cout to log.
    m_logger << "\nWriting Results for mu: " << mu <<
        " finished.\n";
}

results_writer& results_writer::get_instance()
{
    assert(s_instance != nullptr);
    return *s_instance;
}

void results_writer::instantiate(std::ofstream& logger)
{
    assert(s_instance == nullptr);
    s_instance = new results_writer(logger);
}

void results_writer::destroy()
{
    assert(s_instance != nullptr);
    delete s_instance;
    s_instance = nullptr;
}

results_writer::results_writer(std::ofstream& logger)
    : m_is_writer_ready(false),
    m_logger(logger)
{}
