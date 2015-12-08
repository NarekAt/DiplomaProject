#include "three_byte_vertex.h"
#include "graph.h"
#include "constants.h"
#include <fstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

int main()
{
    /// Serializtion first test.
    /*
    std::ofstream ofs("filename");
    graph_types::three_byte_vertex v(15);
    boost::archive::binary_oarchive oa(ofs);
    oa << v;
    ofs.close();
    std::ifstream ifs("filename");
    graph_types::three_byte_vertex v2;
    boost::archive::binary_iarchive ia(ifs);
    ia >> v;
    std::cout << v;
    ifs.close();
    */
    ///
    /// Serializtion second test.
    graph_types::graph g;
    g = graph_types::graph(graph_types::graph_size(12800), graph_types::storage_core_type::BITSETS_FULL);
    return 0;
}
