#pragma once

#include <pogl/uniform-handle.hh>

namespace pogl
{
    template <typename T>
    inline UniformHandle& UniformHandle::operator=(const T&)
    {
        throw std::runtime_error{"Not implemented"};
    }

    template<>
    inline UniformHandle&
    UniformHandle::operator=<float>(const float& value)
    {
        glUniform1f(location_, value);
        return *this;
    }

    template<>
    inline UniformHandle&
    UniformHandle::operator=<glm::mat4>(const glm::mat4& value)
    {
        glUniformMatrix4fv(location_, 1,
                           GL_FALSE, glm::value_ptr(value));
        return *this;
    }

    template<>
    inline UniformHandle&
    UniformHandle::operator=<glm::vec3>(const glm::vec3& value)
    {
        glUniform3f(location_, value.x, value.y, value.z);
        return *this;
    }

    template <>
    inline UniformHandle&
    UniformHandle::operator=<int>(const int& value)
    {
        glUniform1i(location_, value);
        return *this;
    }
} // namespace pogl
