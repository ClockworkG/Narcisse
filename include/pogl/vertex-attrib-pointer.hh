#pragma once

#include <GL/glew.h>

#include <string>

namespace pogl
{
    constexpr GLint INVALID_LOCATION = -1;

    class Program;

    class VertexAttribPointer
    {
        friend Program;

    public:
        ~VertexAttribPointer() = default;

        template <typename VBO>
        VertexAttribPointer& operator=(const VBO& vbo);

        VertexAttribPointer() = delete;
        VertexAttribPointer(const VertexAttribPointer&) = delete;
        VertexAttribPointer(VertexAttribPointer&&) = delete;
        VertexAttribPointer& operator=(VertexAttribPointer&&) = delete;

    private:
        GLint location_ = INVALID_LOCATION;

        VertexAttribPointer(const Program& program,
                            const std::string& name);
    };
} // namespace pogl

#include <pogl/vertex-attrib-pointer.hxx>
