#pragma once

#include "shader.hh"

#include <utility>

namespace pogl
{
    template <GLenum ShaderType>
    Shader<ShaderType>::Shader(detail::ShaderSource&& sources)
        : shader_id_(glCreateShader(ShaderType))
    {
        if (shader_id_ != INVALID_SHADER)
        {
            glShaderSource(shader_id_,
                           sources.count,
                           sources.string,
                           sources.length);

            glCompileShader(shader_id_);
            glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &compilation_success_);
        }
    }

    template <GLenum ShaderType>
    Shader<ShaderType>::~Shader()
    {
        if (shader_id_ != INVALID_SHADER)
        {
            glDeleteShader(shader_id_);
            shader_id_ = INVALID_SHADER;
        }
    }

    template <GLenum ShaderType>
    Shader<ShaderType>::Shader(Shader&& other)
        : shader_id_(std::exchange(other.shader_id_, INVALID_SHADER))
        , compilation_success_(other.compilation_success_)
    {}

    template <GLenum ShaderType>
    auto Shader<ShaderType>::operator=(Shader&& other) -> Shader&
    {
        if (shader_id_ != INVALID_SHADER)
            glDeleteShader(shader_id_);

        shader_id_ = std::exchange(other.shader_id_, INVALID_SHADER);
        compilation_success_ = other.compilation_success_;

        return *this;
    }

    template <GLenum ShaderType>
    Shader<ShaderType>::operator bool() const noexcept
    {
        return shader_id_ != INVALID_SHADER && compilation_success_ != GL_FALSE;
    }

    template <GLenum ShaderType>
    Shader<ShaderType>::operator GLuint() const noexcept
    {
        return shader_id_;
    }

    template <GLenum ShaderType>
    std::string Shader<ShaderType>::error() const
    {
        GLint max_length = 0;
        glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> error_log(max_length);
        glGetShaderInfoLog(shader_id_,
                           max_length,
                           &max_length,
                           &error_log[0]);

        return std::string(begin(error_log), end(error_log));
    }

    template <typename Shader>
    Shader make_shader(const std::string& source)
    {
        auto sources = detail::make_shader_source(source);
        return Shader(std::move(sources));
    }

    template <typename Shader>
    Shader make_shader(const std::filesystem::path& source_path)
    {
        std::vector<std::string> lines;
        std::ifstream shader_stream{source_path};

        if (!shader_stream)
            return Shader();

        for (std::string line; std::getline(shader_stream, line); )
            lines.push_back(line + "\n");

        auto sources = detail::make_shader_source(
            begin(lines), end(lines)
        );
        return Shader(std::move(sources));
    }
} // namespace pogl
