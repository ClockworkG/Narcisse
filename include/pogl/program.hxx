#pragma once

#include <pogl/program.hh>

namespace pogl
{
    template <GLenum ShaderType>
    Program& Program::attach(const Shader<ShaderType>& shader)
    {
        glAttachShader(program_id_, shader);
        shaders_.push_back(shader);
        return *this;
    }
} // namespace pogl
