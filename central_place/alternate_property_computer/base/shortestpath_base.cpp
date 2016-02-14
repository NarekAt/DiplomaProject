#include "shortestpath_base.h"
#include "wave.h"

#include <iterator>
#include <fstream>
#include <stdexcept>

// related with multithreading
#include <future>
#include <mutex>

namespace
{

using namespace Base;
typedef ShortestPathBase::PathLengthProp PathLengthProp;
typedef graph_types::BFS BFS;
typedef graph_types::BFSParams BFSParams;

class BFSIterator : public std::iterator<
                        std::forward_iterator_tag,
                        BFS::ArrivalInfo>
{
    typedef BFS::Vertices                         Vertices;
    typedef BFS::WeightedVertices                 WeightedVertices;
    typedef BFS::ArrivalInfo                      ArrivalInfo;
    typedef BFS::Params<Vertices>                 Params;
    typedef BFS::Params<WeightedVertices>         WeightedParams;
    typedef std::set<unsigned int>                UintSet;
    typedef graph_types::sequence_of_edges::const_iterator EdgeIterator;

    struct DetailedArrivalInfo : ArrivalInfo
    {
        DetailedArrivalInfo()
            : ArrivalInfo()
            , isWinner(true)
        {}

        DetailedArrivalInfo(const ArrivalInfo& vi)
            : ArrivalInfo(vi)
            , isWinner(true)
        {}

        bool isWinner;
    };

public: // types
    typedef std::iterator<
                std::forward_iterator_tag,
                BFS::ArrivalInfo> BaseType;

public: // functions
    explicit BFSIterator(const Params& p);
    explicit BFSIterator(const WeightedParams& p);

    void operator++();
    // TODO: implement operator==(Null null) instead of isValid().
    bool isValid() const;
    ArrivalInfo operator*() const;

private:
    template <class ParamsType>
    void initialize(const ParamsType& p);

    void goToNextNonVisitedVertex();
    void enqueueNonVisitedAdjacentVertices();
    void parallel_process(EdgeIterator first, EdgeIterator last);
    void process(EdgeIterator first, EdgeIterator second);

private: // data
    Wave wave_;
    UintSet visitedVertices_;
    const graph_types::graph g_;
    const double maxDistance_;
    DetailedArrivalInfo currentArrival_;
    const bool reportAllCompetingArrivals_;

    std::mutex mutex_;

    typedef std::map<graph_types::edge, double> EdgeCountProperty;

    static EdgeCountProperty edgeCountProperty_;
};

BFSIterator::EdgeCountProperty BFSIterator::edgeCountProperty_;

BFSIterator::BFSIterator(const Params& p)
    : wave_(p.sources)
    , g_(p.graph)
    , maxDistance_(p.maxDistance)
    , reportAllCompetingArrivals_(p.reportAllCompetingArrivals)
{
    initialize(p);
}

BFSIterator::BFSIterator(const WeightedParams& p)
    : wave_(p.sources)
    , g_(p.graph)
    , maxDistance_(p.maxDistance)
    , reportAllCompetingArrivals_(p.reportAllCompetingArrivals)
{
    initialize(p);
}

template <class ParamsType>
void
BFSIterator::initialize(const ParamsType& p)
{
    goToNextNonVisitedVertex();
}

void
BFSIterator::goToNextNonVisitedVertex()
{
    while (!wave_.empty())
    {
        currentArrival_ = wave_.get();
        wave_.pop();

        const auto ret = visitedVertices_.insert(currentArrival_.m_vertex);
        currentArrival_.isWinner = ret.second;
        if ( currentArrival_.isWinner || reportAllCompetingArrivals_ )
            return;
    }

    currentArrival_ = ArrivalInfo();
    assert(!isValid());
}

void
BFSIterator::enqueueNonVisitedAdjacentVertices()
{
    typedef graph_types::vertex vertex;

    const vertex currentVertex = currentArrival_.m_vertex;

    const auto edges = g_.neighbor_edges_sequence(currentVertex);
    parallel_process(edges.begin(), edges.end());
}

void
BFSIterator::parallel_process(EdgeIterator first, EdgeIterator last)
{
    unsigned long const length = std::distance(first,last);
    if(!length)
        return;

    unsigned long const min_per_thread = 25;
    if(length < (2 * min_per_thread))
    {
        process(first, last);
    }
    else
    {
        EdgeIterator const mid_point = first + length / 2;
        std::future<void> first_half = std::async(&BFSIterator::parallel_process,
                                                  this, first, mid_point);
        parallel_process(mid_point, last);
        first_half.get();
    }
}

void
BFSIterator::process(EdgeIterator first, EdgeIterator last)
{
    typedef graph_types::vertex vertex;
    typedef graph_types::edge edge;
    typedef std::unique_lock<std::mutex> Lock;

    Lock l (mutex_, std::defer_lock);

    const vertex currentVertex = currentArrival_.m_vertex;
    const vertex currentVertexDistance = currentArrival_.m_distance;

    for (; first != last; ++first)
    {
        const edge& edge = *first;
        if ( edge == currentArrival_.m_edge )
            continue;

        const vertex outVertex = (edge.first != currentVertex ? edge.first : edge.second);

        const auto ret = visitedVertices_.find(outVertex);
        const double edgeLength = 1.0;
        if ( ret == visitedVertices_.end() || (reportAllCompetingArrivals_ && outVertex == currentVertex) )
        {
            const double newDistance = currentVertexDistance + edgeLength;
            // critical section
            l.lock();
            if ( newDistance <= maxDistance_ )
                wave_.push(ArrivalInfo(outVertex, edge, currentArrival_.m_source, newDistance));
            l.unlock();
        }
    }
}

inline void
BFSIterator::operator++()
{
    if ( currentArrival_.isWinner )
        enqueueNonVisitedAdjacentVertices();
    goToNextNonVisitedVertex();
}

inline bool
BFSIterator::isValid() const
{
    return currentArrival_.isValid();
}

inline BFS::ArrivalInfo
BFSIterator::operator*() const
{
    return currentArrival_;
}

template <class ParamsType>
BFSIterator::BaseType
makeBFSIterator(const ParamsType& bfsParams)
{
    return BFSIterator(bfsParams);
}

template <class ParamsType, class CollectionType>
void calulate(const graph_types::graph& g,
              const CollectionType& terminalVertices,
              ShortestPathBase::DistanceResultCollection& pathLengths)
{
    const double INVALID_DOUBLE = std::numeric_limits<double>::max();

    ParamsType bfsParams(g, terminalVertices);
    for ( BFSIterator it(bfsParams); it.isValid(); ++it )
    {
        const BFS::ArrivalInfo vertexInf(*it);
        // TODO: implement dbl_eq() and use for this case.
        assert(pathLengths[vertexInf.m_vertex] == INVALID_DOUBLE);
        pathLengths[vertexInf.m_vertex] = vertexInf.m_distance;
    }
}

} // anonymous namespace

namespace graph_types
{

BFSParams::BFSParams(const graph_types::graph& g, vertex source)
    : BaseType(g, Vertices(1, source))
{}

BFSParams::BFSParams(const graph_types::graph& g, const Vertices& sources)
    : BaseType(g, sources)
{}

} // namespace graph_types

namespace Base
{

void
ShortestPathBase::calculate(const graph_types::graph& g, const VertexCollection& terminalVertices, PathLengthProp& pathLengths)
{
    BFSParams bfsParams(g, terminalVertices);
    for ( BFSIterator it(bfsParams); it.isValid() ; ++it )
    {
        const BFS::ArrivalInfo vertexInf(*it);
        pathLengths.insert(std::make_pair(vertexInf.m_vertex, vertexInf.m_distance));
    }
}

void
ShortestPathBase::calculate(const graph_types::graph& g, const VertexCollection& terminalVertices, DistanceResultCollection& pathLengths)
{
    calulate<BFSParams>(g, terminalVertices, pathLengths);
}

void
ShortestPathBase::calculate(const graph_types::graph& g, const WeightedVertexCollection& terminalVertices, DistanceResultCollection& pathLengths)
{
    // NOTE: Implement class BFSWeightedParam when needed.
    // NOTE: Implement this function when needed.

    std::runtime_error("Not Implemented yet");
}

} // namespace Base
