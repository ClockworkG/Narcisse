#pragma once

namespace pogl
{
    inline program_ptr_t Object::get_shader() const
    {
        return shader_;
    }
} // namespace pogl
