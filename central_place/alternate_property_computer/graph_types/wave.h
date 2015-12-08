#ifndef INCLUDED__WAVE_HPP
#define INCLUDED__WAVE_HPP

#include "bfs.h"
#include <queue>

class Wave
{
    typedef graph_types::BFS        BFS;
    typedef BFS::Vertices           Vertices;
    typedef BFS::WeightedVertices   WeightedVertices;
    typedef BFS::ArrivalInfo        ArrivalInfo;

public:
    explicit Wave(const Vertices& vertices)
    {
        for (const auto& v : vertices)
        {
            push(ArrivalInfo(v, graph_types::invalidEdge(), v, 0));
        }
    }

    explicit Wave(const WeightedVertices& vertices)
    {
        for (const auto& v : vertices)
        {
            push(ArrivalInfo(v.first, graph_types::invalidEdge(), v.first, v.second));
        }
    }

    void push(const ArrivalInfo& waveElem)
    {
        wave_.push(waveElem);
    }

    void pop()
    {
        wave_.pop();
    }

    const ArrivalInfo& get() const { return wave_.top(); }
    bool empty() const { return wave_.empty(); }

private:
    typedef std::vector<ArrivalInfo> ContainerType;
    class PriorityPred
    {
    public:
        bool operator() (const ArrivalInfo& lhs, const ArrivalInfo& rhs) const
        {
            return lhs.m_distance < rhs.m_distance;
        }
    };

private:
    std::priority_queue<ArrivalInfo, ContainerType, PriorityPred> wave_;
};


#endif // INCLUDED__WAVE_HPP
