//////////////////////////////////////////////
//     Description:                         //
//          To run and test generator.      //
//                                          //
//                                          //
//////////////////////////////////////////////


#include "generator.h"
#include "graph.h"

#include <gtest/gtest.h>

using namespace graph_types;

TEST(GeneratorTest, ShouldRunGraphGeneratorAndCheckGraphSize)
{
    std::ofstream logger;
    logger.open("log.txt");

    generator gen;
    graph g = gen.run(graph_size(100), 0.3, storage_core_type::BITSETS_FULL, logger);

    EXPECT_EQ(g.size(), 100u);
}
