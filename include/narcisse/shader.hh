#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "detail/shader-source.hh"

namespace pogl
{
    constexpr GLuint INVALID_SHADER = 0;

    template <GLenum ShaderType>
    class Shader
    {
        template <typename Shader>
        friend Shader make_shader(const std::string&);

        template <typename Shader>
        friend Shader make_shader(const std::filesystem::path&);

    public:
        ~Shader();
        Shader(Shader&&);
        Shader& operator=(Shader&&);

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        operator bool() const noexcept;

        std::string error() const;

    private:
        Shader(detail::ShaderSource&& sources);

        GLuint shader_id_ = INVALID_SHADER;
        GLint compilation_success_ = GL_FALSE;
    };

    using vertex_shader_t = Shader<GL_VERTEX_SHADER>;
    using fragment_shader_t = Shader<GL_FRAGMENT_SHADER>;

    template <typename Shader>
    Shader make_shader(const std::string& source);

    template <typename Shader>
    Shader make_shader(const std::filesystem::path& source_path);
} // namespace pogl

#include "shader.hxx"
