#include "parallel_triangle_counter.h"
#include "types.h"

#include <boost/mpi.hpp>
#include <iostream>

std::string help("====================================================================\n"
                 "Graph analyzer is used for reading serialized boost graph file and\n"
                 "calculation of mentioned attribute occurrence quantity in the graph.\n"
                 "Usage:\n"
                 "./graph_analyzer.exe {-triangles | -other} <boost_file_name> \n"
                 "====================================================================\n");

void print_help()
{
    std::cout << help;
}

void arg_count_validation(int argc)
{
    if (1 == argc) {
        print_help();
        exit(1);
    }

    if (3 != argc) {
        std::cout << "ERROR: Count of arguments is incorrect." << std::endl;
        print_help();
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    arg_count_validation(argc);
    std::cout << "argc = " << argc << std::endl;
    for (int i = 0; i < argc; ++i)
        std::cout << "arg[i] = " << argv[i] << std::endl;

    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator comm;
    const std::string attr(argv[1]);
    const std::string infile(argv[2]);
    if ("-triangles" == attr) {
        parallel_triangle_counter tc(comm, infile);
        tc.count();
        tc.write_results();

    } else {
        std::cout << "Other types of attributes are not supported!\n";
    }
    return 0;
}
