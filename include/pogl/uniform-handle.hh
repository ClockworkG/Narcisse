#pragma once

#include <GL/glew.h>
#include <pogl/vertex-attrib-pointer.hh>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <string>

namespace pogl
{
    class Program;

    class UniformHandle
    {
        friend Program;
    public:
        ~UniformHandle() = default;

        template <typename T>
        UniformHandle& operator=(const T& value);

        UniformHandle() = delete;
        UniformHandle(const UniformHandle&) = delete;
        UniformHandle(UniformHandle&&) = delete;
        UniformHandle& operator=(const UniformHandle&) = delete;
        UniformHandle& operator=(UniformHandle&&) = delete;

    private:
        UniformHandle(const Program& program, const std::string& name);

        GLint location_ = INVALID_LOCATION;
        std::string name_;
    };
} // namespace pogl

#include <pogl/uniform-handle.hxx>
