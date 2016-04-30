/**
 * @file main/main.cpp
 * @brief Contains main(...) function call
 */

#include "erdos_renyi_reader.h"
#include "community_detector.h"
#include "writer.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <boost/filesystem.hpp>

namespace {
    const std::string GRAPH_FILE_NAME_PREFIX = "./community_graphs/community_graph_";

    std::string createLogFile()
    {
        auto d = boost::filesystem::status("./community_graphs/Logs");
        if (!boost::filesystem::exists(d)) {
            boost::filesystem::create_directory("./community_graphs/Logs");
        }

        std::string file_name = std::string("./community_graphs/Logs") + std::string("community_") +
                std::string(".log");
        auto f = boost::filesystem::status(file_name);
        assert(!boost::filesystem::exists(f));
        return file_name;
    }

    void createCommunityDirectory() {
        auto d = boost::filesystem::status("./community_graphs");
        if (!boost::filesystem::exists(d)) {
            boost::filesystem::create_directory("./community_graphs");
        }
    }

    void outputGraphs(std::vector<graph_types::graph> graphs) {
        createCommunityDirectory();

        writer w;
        std::ofstream logger;
        logger.open(createLogFile());

        for(int i = 0; i < graphs.size(); ++i)
        {
            std::string filePath = GRAPH_FILE_NAME_PREFIX + std::to_string(i);
            w.run(graphs[i], graphs[i].size(), -1, filePath, logger);
        }
    }
}


int main(int argc, char* argv[])
{
    std::string graph_path = argv[1];

    erdos_renyi_reader reader;
    graph_types::graph graph (graph_types::storage_core_type::BITSETS_FULL);


    unsigned vertex_count;
    double probability;
    reader.get_graph_and_properties_from_file(graph_path,
                       graph, vertex_count, probability);

    community::ComboDetector detector(graph);
    outputGraphs(detector.getCommunityGraphs());

    return 0;
}
