#pragma once

#include <cstring>
#include <string>
#include <type_traits>

#include <GL/glew.h>

namespace pogl::detail
{
    struct ShaderSource
    {
        ShaderSource() = default;
        ~ShaderSource();
        ShaderSource(ShaderSource&&) = default;
        ShaderSource& operator=(ShaderSource&&) = default;

        ShaderSource(const ShaderSource&) = delete;
        ShaderSource& operator=(const ShaderSource&) = delete;

        GLsizei count;
        GLchar** string = nullptr;
        GLint* length = nullptr;
    };

    template <typename Iterator>
    ShaderSource make_shader_source(Iterator begin, Iterator end);

    ShaderSource make_shader_source(const std::string& source);
} // namespace pogl::detail

#include "shader-source.hxx"
