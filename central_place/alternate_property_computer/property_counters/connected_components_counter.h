#ifndef INCLUDED__CONNECTED_COMPONENTS_COUNTER_HPP
#define INCLUDED__CONNECTED_COMPONENTS_COUNTER_HPP

#include <vector>

namespace graph_types
{
    class graph;
}

class ConnectedComponentsCounter
{
public:
    typedef std::vector<unsigned long>  ResultCollection;

public:
    static ResultCollection calculate(const graph_types::graph& graph);
};

#endif
