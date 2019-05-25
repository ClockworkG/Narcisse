#pragma once

#include <GL/glew.h>

namespace pogl
{
    class Program
    {
    public:
        Program();
        ~Program();
        Program(Program&&);
        Program& operator=(Program&&);

        Program(const Program&) = delete;
        Program& operator=(const Program&) = delete;

    private:
        GLuint program_id_;
    };
} // namespace pogl
