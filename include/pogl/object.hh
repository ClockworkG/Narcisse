#pragma once

#include <GL/glew.h>

#include <pogl/camera.hh>
#include <pogl/vbo.hh>
#include <pogl/program.hh>

namespace pogl
{
    constexpr GLuint INVALID_VAO = 0;

    class Object
    {
    public:
        Object(VBO<float>&& vertices,
               program_ptr_t program = nullptr);
        ~Object();
        Object(Object&&);
        Object& operator=(Object&&);

        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;

        void operator()(const Camera& cam) const;

    private:
        GLuint vao_id_ = INVALID_VAO;
        VBO<float> vertices_;
        program_ptr_t program_ = nullptr;
    };
} // namespace pogl
