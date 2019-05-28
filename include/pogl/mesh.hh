#pragma once

#include <GL/glew.h>

#include <pogl/vbo.hh>
#include <pogl/program.hh>

namespace pogl
{
    constexpr GLuint INVALID_VAO = 0;

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();
        Mesh(Mesh&&);
        Mesh& operator=(Mesh&&);

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void operator()() const;

    private:
        GLuint vao_id_ = INVALID_VAO;
    };
} // namespace pogl
