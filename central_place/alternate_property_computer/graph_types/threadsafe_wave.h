#ifndef INCLUDED__THREADSAFE_WAVE_HPP
#define INCLUDED__THREADSAFE_WAVE_HPP

#include "bfs.h"
#include <queue>

// related with multithreading
#include <mutex>
#include <condition_variable>

class ThreadSafeWave
{
    typedef graph_types::BFS        BFS;
    typedef BFS::Vertices           Vertices;
    typedef BFS::WeightedVertices   WeightedVertices;
    typedef BFS::ArrivalInfo        ArrivalInfo;

    typedef std::lock_guard<std::mutex> LockGuard;
    typedef std::unique_lock<std::mutex> UniqueLock;

public:
    explicit ThreadSafeWave(const Vertices& vertices)
    {
        LockGuard lock(mutex_);

        for (const auto& v : vertices)
        {
            push(ArrivalInfo(v, graph_types::invalidEdge(), v, 0));
        }
    }

    explicit ThreadSafeWave(const WeightedVertices& vertices)
    {
        LockGuard lock(mutex_);

        for (const auto& v : vertices)
        {
            push(ArrivalInfo(v.first, graph_types::invalidEdge(), v.first, v.second));
        }
    }

    void push(const ArrivalInfo& waveElem)
    {
        UniqueLock lock(mutex_);

        wave_.push(waveElem);
        condVar_.notify_one();
    }

    void wait_and_pop()
    {
        UniqueLock lock(mutex_);

        // NOTE: Actually, & -- is a workaround for GCC bug
        condVar_.wait(lock, [&]{return !wave_.empty();});
        wave_.pop();
    }

    bool try_pop()
    {
        LockGuard lock(mutex_);

        if (wave_.empty())
            return false;
        wave_.pop();
        return true;
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
    std::mutex mutex_;
    std::condition_variable condVar_;
};

#endif // INCLUDED__THREADSAFE_WAVE_HPP
