#ifndef INCLUDED__BFS_HPP
#define INCLUDED__BFS_HPP

#include "graph.h"

namespace graph_types
{

class BFS
{
public:
    struct ArrivalInfo
    {
        ArrivalInfo()
            : m_vertex(graph_types::invalidVertex())
            , m_edge(graph_types::invalidEdge())
            , m_source(graph_types::invalidVertex())
            , m_distance(std::numeric_limits<double>::infinity())
        {}

        ArrivalInfo(const graph_types::vertex v,
                    const graph_types::edge e,
                    const graph_types::vertex s,
                    const double d)
            : m_vertex(v)
            , m_edge(e)
            , m_source(s)
            , m_distance(d)
        {}

        bool isValid() const
        {
            return m_vertex != graph_types::invalidVertex();
        }

        // The vertex at which the traversal arrived
        graph_types::vertex m_vertex;

        // The edge through which the traversal
        // arrived at the current vertex
        graph_types::edge m_edge;

        // Reference to the source vertex
        graph_types::vertex m_source;

        // The length of the path through which the
        // traversal arrived at the current vertex
        double m_distance;
    };

public:
    typedef std::pair<graph_types::vertex, double> WeightedVertex;
    typedef std::vector<WeightedVertex>            WeightedVertices;
    typedef graph_types::sequence_of_vertices      Vertices;

    template <class Container>
    struct Params
    {
        typedef typename Container::value_type value_type;

        // Graph to be traversed
        const graph_types::graph graph;

        // The source vertices
        const Container sources;

        // Limit the traversal to vertices whose distance from the sources
        // does NOT exceed this value
        // This parameters is optional and defaults to +infinity.
        double  maxDistance;

        // If set to true, all competing arrivals to the same
        // vertex are reported. This actually allows to perform a BFS-like
        // traversal on edges rather than vertices.
        // This parameters is optional and defaults to false.
        bool reportAllCompetingArrivals;

        // This constructor enforces initialization of mandatory parameters
        // NOTE: For a BFS traversal with a single source vertex or
        // NOTE: a collection of source vertices stored in a container
        // NOTE: see the convenience class BFSParams below

        Params(const graph_types::graph& g, const Container& s)
            : graph(g)
            , sources(s)
            , maxDistance(std::numeric_limits<double>::max())
            , reportAllCompetingArrivals(false)
        {}
    };
};

// A convenience utility for configuring BFS with a single source vertex
// or a collection of source vertices stored in a container
struct BFSParams : BFS::Params<BFS::Vertices>
{
    typedef BFS::Params<BFS::Vertices>          BaseType;
    typedef BaseType::value_type                vertex;
    typedef graph_types::sequence_of_vertices   Vertices;

    BFSParams(const graph_types::graph& g, vertex source);
    BFSParams(const graph_types::graph& g, const Vertices& sources);
};

} // namespace graph_types

#endif // INCLUDED__BFS_HPP
