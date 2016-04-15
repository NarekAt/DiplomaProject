#include "eigenvector_centrality.h"
#include "igraph.h"
#include <math.h>
#include <cassert>

namespace
{

void
print_vector(igraph_vector_t *v, FILE *f)
{
    long int i;
    for (i = 0; i < igraph_vector_size(v); i++)
    {
        fprintf(f, " %li", (long int) VECTOR(*v)[i]);
    }
    fprintf(f, "\n");
}

void
prepareIGraph(const igraph_vector_t& edges,
              const graph_types::sequence_of_edges& edgesSequence)
{
    const auto edgesCount = edgesSequence.size();

    for (unsigned i = 0, j = 0; i < edgesCount && j < 2 * edgesCount; ++i, ++j)
    {
        const auto e = edgesSequence[i];
        VECTOR(edges)[j] = e.first;
        VECTOR(edges)[++j] = e.second;
    }
}

} // anonymous namespace

namespace Base
{

void
EVC::computeImpl()
{
    igraph_t graph;

    const auto size = graph_.size();
    assert(size != 0);
    const int ret = igraph_empty(&graph, size, 0);
    assert(ret != IGRAPH_EINVAL);

    const auto edgesSequence = graph_.edges_sequence();
    igraph_vector_t edges;
    igraph_vector_init(&edges, 2 * edgesSequence.size());
    prepareIGraph(edges, edgesSequence);

    igraph_add_edges(&graph, &edges, 0);
    igraph_real_t value;
    igraph_vector_t v;
    igraph_vector_init(&v, 0);

    igraph_arpack_options_t options;
    igraph_arpack_options_init(&options);

    igraph_eigenvector_centrality(&graph, &v, &value, 0, 0, 0, &options);

    for (unsigned i=0; i < igraph_vector_size(&v); ++i)
    {
        results_.push_back(VECTOR(v)[i]);
    }

    igraph_vector_destroy(&edges);
    igraph_destroy(&graph);
    igraph_vector_destroy(&v);
}

alternate_property_type
EVC::typeImpl() const
{
    return EIGENVECTOR_CENTRALITY;
}

EVC::ResultType
EVC::getDistributionImpl() const
{
    throw std::logic_error("Property Distribution is meaningless for EigenVectorCentrality");
    return ResultType();
}

} // namespace Base
