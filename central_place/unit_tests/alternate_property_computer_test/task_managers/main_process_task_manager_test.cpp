/////////////////////////////////////////////////////
//
//      Description:
//
//
/////////////////////////////////////////////////////

#include "main_process_task_manager.h"
#include "graph_types.h"

#include "gtest/gtest.h"

namespace
{

using namespace graph_types;

TEST(MainProcessTaskManagerTest)
{
    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator world;
    std::ofstream logger;
    if (0 == world.rank() || 1 == world.size()) {
        logger.open(get_log_file_name());
    }

}
}
