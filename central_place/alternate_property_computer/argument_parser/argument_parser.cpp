/**
 * @file argument_parser/argument_parser.cpp
 * @brief definition of class argument_parser.
 */

#include "argument_parser.h"
#include <assert.h>
#include <iostream>

argument_parser* argument_parser::s_instance = nullptr;

arg_name_to_value_map argument_parser::parse_and_get_args(
    int argc, char* argv[], int rank_of_process) const
{
    arg_name_to_value_map a_n_v;
    if (0 != rank_of_process) {
        return a_n_v;
    }
    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(
            boost::program_options::parse_command_line(
                argc, argv, m_options_description), vm);
        if (1 == vm.count("graph_file")) {
            a_n_v.insert(std::make_pair(
                std::string("graph_file"),
                vm["graph_file"].as<std::string>()));
        } else {
            // TODO: throw exception.
        }
        if (1 == vm.count("mu_file")) {
            a_n_v.insert(std::make_pair(
                std::string("mu_file"),
                vm["mu_file"].as<std::string>()));
        } else {
            // TODO: throw exception.
        }
        if (1 == vm.count("step_count")) {
            a_n_v.insert(std::make_pair(
                std::string("step_count"),
                vm["step_count"].as<unsigned>()));
        } else {
            // TODO: throw exception.
        }
        if (1 == vm.count("randomization_type")) {
            auto r_t = get_randomization_type_by_name(
                vm["randomization_type"].as<std::string>());
            if (randomization_type::INVALID_RT == r_t) {
                // TODO: throw exception.
            }
            a_n_v.insert(std::make_pair(
                std::string("randomization_type"), r_t));
        } else if (0 == vm.count("randomization_type")) {
            auto r_t = get_randomization_type_by_name(
                "random_switch");
            if (randomization_type::INVALID_RT == r_t) {
                assert(!"invalid randomization type");
            }
            a_n_v.insert(std::make_pair(
                std::string("randomization_type"), r_t));
        } else {
            // TODO: throw exception
        }
        if (1 == vm.count("alternate_property_type")) {
            auto ap_t = get_alternate_property_type_by_name(
                vm["alternate_property_type"].as<std::string>());
            if (alternate_property_type::INVALID_APT == ap_t) {
                // TODO: throw exception.
            }
            a_n_v.insert(std::make_pair(
                std::string("alternate_property_type"), ap_t));
        } else if (0 == vm.count("alternate_property_type")) {
            auto ap_t = get_alternate_property_type_by_name(
                "triangle_count");
            if (alternate_property_type::INVALID_APT == ap_t) {
                assert(!"invalid alternate property type");
            }
            a_n_v.insert(std::make_pair(
                std::string("alternate_property_type"), ap_t));
        } else {
            // TODO: throw exception
        }
        boost::program_options::notify(vm);
    } catch (const boost::program_options::error& e) {
        // TODO: Change cout to log.
        std::cerr << "\nError parsing command line: " << e.what() << std::endl << std::endl;
        m_logger << m_options_description;
        // TODO throw exception.
    }   // TODO: catch parsing exception and throw up.
    return a_n_v;
}

argument_parser& argument_parser::get_instance()
{
    assert(s_instance != nullptr);
    return *s_instance;
}

void argument_parser::instantiate(std::ofstream& logger)
{
    assert(s_instance == nullptr);
    s_instance = new argument_parser(logger);
}

void argument_parser::destroy()
{
    assert(s_instance != nullptr);
    delete s_instance;
    s_instance = nullptr;
}

argument_parser::argument_parser(std::ofstream& logger) :
    m_logger(logger)
{
    m_options_description.add_options()
        ("graph_file,g", 
            boost::program_options::value<std::string>()->required(),
            "File which contains graph")
        ("mu_file,m", 
            boost::program_options::value<std::string>()->required(), 
            "File which contains mu sequence or mu range with step")
        ("step_count,c", 
            boost::program_options::value<unsigned>()->required(), 
            "Step count per generation.")
        ("randomization_type,r_t", 
            boost::program_options::value<std::string>(),
            "Randomization type.")
        ("alternate_property_type,a_p_t",
            boost::program_options::value<std::string>(),
            "Alternate_property_type: by default triangle_count");
}
