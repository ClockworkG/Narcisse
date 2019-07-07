#pragma once

#include <pogl/program.hh>

namespace pogl
{
    template <GLenum ShaderType>
    Program& Program::attach(const Shader<ShaderType>& shader)
    {
        glAttachShader(program_id_, shader.shader_id_);
        shaders_.push_back(shader.shader_id_);
        return *this;
    }

    template <GLenum ShaderType>
    Program& Program::operator+=(const Shader<ShaderType>& shader)
    {
        return this->attach(shader);
    }

    inline auto with_shader(const Program& shader, display_fun_t&& fun)
    {
        return [&shader, fun = std::move(fun)]()
        {
            glUseProgram(shader);
            fun(shader);
            glUseProgram(INVALID_PROGRAM);
        };
    }
} // namespace pogl
