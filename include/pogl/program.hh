#pragma once

#include <istream>
#include <list>
#include <ostream>

#include <GL/glew.h>

#include <pogl/shader.hh>

namespace pogl
{
    constexpr GLuint INVALID_PROGRAM = 0;

    class Program
    {
    public:
        Program();
        ~Program();
        Program(Program&&);
        Program& operator=(Program&&);

        Program(const Program&) = delete;
        Program& operator=(const Program&) = delete;

        template <GLenum ShaderType>
        Program& attach(const Shader<ShaderType>& shader);

        template <GLenum ShaderType>
        Program& operator+=(const Shader<ShaderType>& shader);

        bool link();
        std::string error() const;

        operator GLuint() const noexcept;

    private:
        GLuint program_id_ = INVALID_PROGRAM;
        std::list<GLuint> shaders_;

        void detach_all();
    };

    std::ostream& operator<<(std::ostream& os, const Program& program);
    std::istream& operator>>(std::istream& is, Program& program);
} // namespace pogl

#include <pogl/program.hxx>
