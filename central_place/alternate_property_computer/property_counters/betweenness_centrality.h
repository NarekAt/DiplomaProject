#ifndef INCLUDED__BETWEENNESS_CENTRALITY_HPP
#define INCLUDED__BETWEENNESS_CENTRALITY_HPP

#include "graph_types.h"
#include <vector>

namespace graph_types
{
    class graph;
}

class BC
{
public:
    typedef unsigned long       IndexType;
    typedef graph_types::vertex vertex;
    typedef std::vector<IndexType> ResultCollection;

public:
    static ResultCollection calculate(const graph_types::graph& g);
};

#endif
