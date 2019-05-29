#pragma once

namespace pogl
{
    inline const Camera& Scene::get_camera() const noexcept
    {
        return settings_.camera;
    }
} // namespace pogl
