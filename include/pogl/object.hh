#pragma once

#include <GL/glew.h>

#include <pogl/mesh.hh>
#include <pogl/program.hh>
#include <pogl/camera.hh>
#include <pogl/vbo.hh>
#include <pogl/legacy/image.hh>
#include <pogl/texture.hh>

namespace pogl
{
    struct RenderContext;

    using program_ptr_t = std::shared_ptr<pogl::Program>;

    constexpr GLuint INVALID_VAO = 0;

    class Object
    {
    public:
        Object(const Mesh& mesh,
               program_ptr_t shader,
               tifo::rgb24_image&& texture);
        ~Object();
        Object(Object&&);
        Object& operator=(Object&&);

        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;

        void render(const RenderContext& context) const;
        void render(const RenderContext& context, const Texture& texture) const;

        void set_position(glm::vec3&& position);
        void set_rotation(glm::vec3&& rotation);
        void set_scale(glm::vec3&& scale);

        const glm::vec3& get_position() const;

    private:
        GLuint vao_id_ = INVALID_VAO;
        vbo_vec3_t vertices_;
        vbo_vec3_t normals_;
        vbo_vec2_t uv_;
        program_ptr_t shader_;
        tifo::rgb24_image texture_data_;
        Texture texture_;

        glm::vec3 position_;
        glm::vec3 rotation_;
        glm::vec3 scale_;
    };
} // namespace pogl

#include <pogl/object.hxx>
