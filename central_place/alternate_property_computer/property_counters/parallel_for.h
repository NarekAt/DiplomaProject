#ifndef INCLUDED__PARALLEL_FOR_HPP
#define INCLUDED__PARALLEL_FOR_HPP

#include <future>

namespace MT
{

template <class Function>
void parallel_for(unsigned int first, unsigned int last, Function f)
{
    const unsigned int length = last - first + 1;
    if(0 == length)
        return;

    unsigned int const min_per_thread = 25;

    if (length < (2 * min_per_thread))
    {
        for (; first <= last; ++first)
        {
            f(first);
        }
    }
    else
    {
        const unsigned int mid_point = first + length / 2;
        std::future<void> first_half = std::async(&parallel_for<Function>, first, mid_point, f);
        parallel_for(mid_point + 1, last, f);
        first_half.get();
    }
}

}

#endif
