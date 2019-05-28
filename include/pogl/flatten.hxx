#pragma once

#include <pogl/flatten.hh>

namespace pogl
{
    template <typename T>
    std::size_t FlattenPolicy<T>::size()
    {
        return 1;
    }

    template <typename T>
    template <typename ItInput, typename ItOutput>
    void FlattenPolicy<T>::copy(ItInput in_begin,
                                ItInput in_end,
                                ItOutput end_begin)
    {
        std::copy(in_begin, in_end, end_begin);
    }
} // namespace pogl
