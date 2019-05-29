#pragma once

namespace pogl
{
    template <typename VBO>
    VertexAttribPointer& VertexAttribPointer::operator=(const VBO& vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(location_, VBO::stride, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(location_);

        return *this;
    }
} // namespace pogl
