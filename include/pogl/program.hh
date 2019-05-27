#pragma once

#include <list>
#include <string>
#include <vector>

#include <GL/glew.h>

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

        template <typename Shader>
        Program& attach(const Shader& shader);

        bool operator()();
        std::string error() const;

    private:
        GLuint program_id_ = INVALID_PROGRAM;
        std::list<GLuint> shaders_;

        void detach_all();
    };
} // namespace pogl

#include <pogl/program.hxx>
