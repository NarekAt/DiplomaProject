/**
 * @file argument_parser/argument_parser.cpp
 * @brief definition of class argument_parser.
 */

#include "argument_parser.h"
#include "graph_types.h"
#include <assert.h>
#include <iostream>

argument_parser* argument_parser::s_instance = nullptr;

arg_name_to_value_map argument_parser::parse_and_get_args(
    int argc, char* argv[]) const
{
    arg_name_to_value_map a_n_v;
    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(
            boost::program_options::parse_command_line(
                argc, argv, m_options_description), vm);

        if (1 == vm.count("model")) {
            a_n_v.insert(std::make_pair(
                "model",
                vm["model"].as<std::string>()));
        } else {
            // TODO: throw exception
        }
        if (1 == vm.count("size")) {
            a_n_v.insert(std::make_pair(
                "size",
                vm["size"].as<unsigned>()));
        } else {
            // TODO: throw exception.
        }
        if (1 == vm.count("probability")) {
            assert(boost::any_cast<std::string>(a_n_v["model"]) == "erdos_renyi");
            auto p = vm["probability"].as<double>();
            if (p < 0.0 || p > 1.0) {
                // TODO: throw exception.
            }
            a_n_v.insert(std::make_pair(
                "probability", p));
        }
        if (1 == vm.count("edges")) {
            assert(boost::any_cast<std::string>(a_n_v["model"]) == "block_hierarchy");
            auto e = vm["edges"].as<unsigned>();

            a_n_v.insert(std::make_pair(
                "edges", e));
        }
        if (1 == vm.count("output_file")) {
            a_n_v.insert(std::make_pair(
                "output_file",
                vm["output_file"].as<std::string>()));
        } else {
            // TODO: throw exception.
        }
        if (1 == vm.count("core_type")) {
            auto c_t = graph_types::get_core_type_by_name(
                vm["core_type"].as<std::string>());
            if (graph_types::storage_core_type::INVALID_CT == c_t) {
                // TODO: throw exception.
            }
            a_n_v.insert(std::make_pair(
                std::string("core_type"), c_t));
        } else if (0 == vm.count("core_type")) {
            auto c_t = graph_types::get_core_type_by_name(
                "autodetect");
            if (graph_types::storage_core_type::INVALID_CT == c_t) {
                assert(!"invalid core type");
            }
            a_n_v.insert(std::make_pair(
                std::string("core_type"), c_t));
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
        ("model,M",
            boost::program_options::value<std::string>()->required(),
            "Random graph generation model, [erdos_renyi, block_hierarchy]")
        ("size,N",
            boost::program_options::value<unsigned>()->required(),
            "Size of graph")
        ("probability,p",
            boost::program_options::value<double>(), 
            "Probability of edge, valid range is [0.0, 1.0]")
        ("edges,E",
            boost::program_options::value<unsigned>(),
            "Number of edges")
        ("output_file,f",
            boost::program_options::value<std::string>()->required(),
            "Output file path")
        ("core_type,t",
            boost::program_options::value<std::string>(),
            "Core data type of graph: valid values are\n"
            "bitsets_full, bitsets_partion, "
            "sorted_vectors_full, sorted_vectors_partial, autodetect");
}
