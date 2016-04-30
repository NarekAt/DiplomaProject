#ifndef COMMUNITY_DETETCTOR_H
#define COMMUNITY_DETETCTOR_H

#include "graph.h"

namespace community
{

class ComboDetector
{
public:
    typedef std::vector<graph_types::graph> ResultType;

    ComboDetector(const graph_types::graph& g);

    ResultType getCommunityGraphs() const;

private:
    const graph_types::graph& graph_;
};

}
#endif
