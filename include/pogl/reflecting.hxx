#pragma once

#include <pogl/reflecting.hh>

namespace pogl
{
    inline void Reflecting::set_object(Object* object)
    {
        object_ = object;
    }

    inline Object* Reflecting::get_object() const
    {
        return object_;
    }
} // namespace pogl
