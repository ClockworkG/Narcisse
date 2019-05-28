#pragma once

#include <cstdint>

namespace pogl
{
    template <typename T>
    struct FlattenPolicy
    {
        using value_type = T;

        static std::size_t size();

        template <typename ItInput, typename ItOutput>
        static void copy(ItInput in_begin, ItInput in_end, ItOutput out_begin);
    };
} // namespace pogl

#include <pogl/flatten.hxx>
