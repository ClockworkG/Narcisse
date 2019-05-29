#pragma once

#include <GL/glew.h>

#include <pogl/mesh.hh>
#include <pogl/program.hh>
#include <pogl/camera.hh>
#include <pogl/vbo.hh>

namespace pogl
{
    using program_ptr_t = std::shared_ptr<pogl::Program>;

    constexpr GLuint INVALID_VAO = 0;

    class Object
    {
    public:
        Object(const Mesh& mesh,
               program_ptr_t shader);
        ~Object();
        Object(Object&&);
        Object& operator=(Object&&);

        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;

        void display(const Camera& cam) const;

    private:
        GLuint vao_id_ = INVALID_VAO;
        vbo_vec3_t vertices_;
        vbo_vec3_t normals_;
        program_ptr_t shader_;
    };
} // namespace pogl
