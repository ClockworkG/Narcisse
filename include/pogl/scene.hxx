#pragma once

namespace pogl
{
    inline const Camera& Scene::get_camera() const noexcept
    {
        return settings_.camera;
    }

    inline auto Scene::begin() const -> const_iterator
    {
        return std::begin(objects_);
    }

    inline auto Scene::end() const -> const_iterator
    {
        return std::end(objects_);
    }

    inline auto Scene::begin() -> iterator
    {
        return std::begin(objects_);
    }

    inline auto Scene::end() -> iterator
    {
        return std::end(objects_);
    }
} // namespace pogl
