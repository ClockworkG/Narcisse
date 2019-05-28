#pragma once

#include <pogl/camera.hh>

namespace pogl
{
    inline const glm::mat4& Camera::get_view() const noexcept
    {
        return view_;
    }

    inline const glm::mat4& Camera::get_projection() const noexcept
    {
        return projection_;
    }
} // namespace pogl
