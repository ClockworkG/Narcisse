#pragma once

#include <GL/glew.h>

#include <pogl/vbo.hh>
#include <pogl/mesh.hh>

namespace pogl
{
    constexpr GLuint INVALID_VAO = 0;

    class Object
    {
    public:
        Object(const Mesh& mesh);
        ~Object();
        Object(Object&&);
        Object& operator=(Object&&);

        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;

        void display() const;

    private:
        GLuint vao_id_ = INVALID_VAO;
        VBO<float> vertices_;
    };
} // namespace pogl
