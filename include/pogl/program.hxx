#pragma once

#include <pogl/program.hh>

namespace pogl
{
    template <typename Shader>
    Program& Program::attach(const Shader& shader)
    {
        glAttachShader(program_id_, shader);
        shaders_.push_back(shader);
        return *this;
    }
} // namespace pogl
