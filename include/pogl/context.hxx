#pragma once

#include <pogl/context.hh>

namespace pogl
{
    template <typename Func>
    void set_callback(Func&& func)
    {
        glutDisplayFunc(func);
    }
} // namespace pogl
