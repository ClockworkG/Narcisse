#pragma once

namespace pogl
{
    inline void Object::set_position(glm::vec3&& position)
    {
        position_ = position;
    }

    inline void Object::set_rotation(glm::vec3&& rotation)
    {
        rotation_ = rotation;
    }

    inline void Object::set_scale(glm::vec3&& scale)
    {
        scale_ = scale;
    }

    inline const glm::vec3& Object::get_position() const
    {
        return position_;
    }
} // namespace pogl
