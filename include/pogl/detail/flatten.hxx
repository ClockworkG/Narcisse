#pragma once

#include <pogl/detail/flatten.hh>

namespace pogl::detail
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

    template<>
    inline std::size_t FlattenPolicy<glm::vec3>::size()
    {
        return 3;
    }

    template<>
    template <typename InIt, typename OutIt>
    inline void FlattenPolicy<glm::vec3>::copy(InIt in_begin, InIt in_end, OutIt out_begin)
    {
        for (auto it = in_begin; it != in_end; it++)
        {
            *out_begin = (*it)[0];
            *(out_begin + 1) = (*it)[1];
            *(out_begin + 2) = (*it)[2];
            out_begin += 3;
        }
    }

    template<>
    inline std::size_t FlattenPolicy<glm::vec2>::size()
    {
        return 2;
    }

    template<>
    template <typename InIt, typename OutIt>
    inline void FlattenPolicy<glm::vec2>::copy(InIt in_begin, InIt in_end, OutIt out_begin)
    {
        for (auto it = in_begin; it != in_end; it++)
        {
            *out_begin = (*it)[0];
            *(out_begin + 1) = (*it)[1];
            out_begin += 2;
        }
    }
} // namespace pogl::detail
