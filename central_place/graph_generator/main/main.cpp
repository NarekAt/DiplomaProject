/**
 * @file main/main.cpp
 * @brief Contains main(...) function call
 */

#include "package.h"
#include "argument_parser.h"
#include "coordinator.h"
#include <iostream>
#include <fstream>
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
    std::string file_name = std::string("./Logs/") + std::string("gen_") + 
        std::string(buf) + std::string(".log");
    auto f = boost::filesystem::status(file_name);
    assert(!boost::filesystem::exists(f));
    return file_name;
}

}

int main(int argc, char* argv[])
{
    std::ofstream logger;
    logger.open(get_log_file_name());
    package::init(logger);
    auto& a_p = argument_parser::get_instance();
    auto& c = coordinator::get_instance();
    c.init(a_p.parse_and_get_args(argc, argv));
    c.run();
    package::uninit();
    return 0;
}
