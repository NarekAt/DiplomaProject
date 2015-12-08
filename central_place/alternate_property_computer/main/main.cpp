/**
 * @file main/main.cpp
 * @brief Contains main(...) function call
 */
#include "package.h"
#include "argument_parser.h"
#include "mediator.h"
#include "exception_base.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <boost/filesystem.hpp>

namespace {

std::string get_log_file_name()
{
    auto d = boost::filesystem::status("./Logs");
    if (!boost::filesystem::exists(d)) {
        boost::filesystem::create_directory("./Logs");
    }
    auto tt = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    auto ptm = std::localtime(&tt);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y.%m.%d_%H.%M.%S", ptm);
    std::string file_name = std::string("./Logs/") + std::string("apc_") + 
        std::string(buf) + std::string(".log");
    auto f = boost::filesystem::status(file_name);
    assert(!boost::filesystem::exists(f));
    return file_name;
}

}

int main(int argc, char* argv[])
{
    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator world;
    std::ofstream logger;
    if (0 == world.rank() || 1 == world.size()) {
        logger.open(get_log_file_name());
    }
    package::init(logger);
    auto& a_p = argument_parser::get_instance();
    auto& m = mediator::get_instance();
    try {
        m.init(a_p.parse_and_get_args(argc, argv, world.rank()));
        m.run(world);
    } catch (const exception_base& e) {
        // Only main process can abort environment
        // and write info, warning and error messages.
        if (0 == world.rank()) {
            // TODO: Change cout to log.
            logger << std::endl << "ERROR: "
                << e.get_message() << std::endl;
            package::uninit();
            logger.close();
            env.abort(-1);
        }
    }
    package::uninit();
    return 0;
}
