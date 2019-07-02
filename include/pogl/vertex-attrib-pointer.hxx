#pragma once

#include <stdexcept>
#include <pogl/detail/gl-types.hh>

namespace pogl
{
    template <typename VBO>
    VertexAttribPointer& VertexAttribPointer::operator=(const VBO& vbo)
    {
        if (location_ == INVALID_LOCATION)
            return *this;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(location_,
                              VBO::stride,
                              gl_types[hana::type_c<typename VBO::value_type>],
                              GL_FALSE,
                              0, NULL);
        glEnableVertexAttribArray(location_);

        return *this;
    }
} // namespace pogl
