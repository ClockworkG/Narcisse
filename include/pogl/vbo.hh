#pragma once

#include <algorithm>
#include <vector>

#include <GL/glew.h>

namespace pogl
{
    constexpr GLuint INVALID_VBO = 0;

    template <typename T>
    class VBO
    {
    public:
        template <typename Iterator>
        VBO(Iterator begin, Iterator end);
        ~VBO();
        VBO(VBO&&);
        VBO& operator=(VBO&&);

        VBO(const VBO&) = delete;
        VBO& operator=(const VBO&) = delete;

    private:
        GLuint vbo_id_ = INVALID_VBO;
        std::vector<T> data_;
    };
} // namespace pogl

#include <pogl/vbo.hxx>
