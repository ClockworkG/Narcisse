#include <pogl/object.hh>
#include <pogl/engine.hh>
#include <pogl/render-target.hh>
#include <glm/gtc/matrix_transform.hpp>

namespace pogl
{
    Object::Object(const Mesh& mesh, program_ptr_t shader,
                   tifo::rgb24_image&& texture)
        : vao_id_(INVALID_VAO)
        , vertices_(begin(mesh.vertices), end(mesh.vertices))
        , normals_(begin(mesh.normals), end(mesh.normals))
        , uv_(begin(mesh.uv), end(mesh.uv))
        , shader_(shader)
        , texture_data_(std::move(texture))
        , texture_(Texture::Dimension{texture_data_.sx, texture_data_.sy}, texture_data_.pixels)
    {
        glGenVertexArrays(1, &vao_id_);
        glBindVertexArray(vao_id_);

        shader_->attrib("position") = vertices_;
        shader_->attrib("normal") = normals_;
        shader_->attrib("uv_map") = uv_;
    }

    Object::~Object()
    {
        if (vao_id_ != INVALID_VAO)
            glDeleteVertexArrays(1, &vao_id_);

        vao_id_ = INVALID_VAO;
    }

    Object::Object(Object&& other)
        : vao_id_(std::exchange(other.vao_id_, INVALID_VAO))
        , vertices_(std::move(other.vertices_))
        , normals_(std::move(other.normals_))
        , uv_(std::move(other.uv_))
        , shader_(std::move(other.shader_))
        , texture_data_(std::move(other.texture_data_))
        , texture_(std::move(other.texture_))
        , position_(std::move(other.position_))
        , rotation_(std::move(other.rotation_))
        , scale_(std::move(other.scale_))
    {}

    Object& Object::operator=(Object&& other)
    {
        if (vao_id_ != INVALID_VAO)
            glDeleteVertexArrays(1, &vao_id_);

        vao_id_ = std::exchange(other.vao_id_, INVALID_VAO);
        vertices_ = std::move(other.vertices_);
        normals_ = std::move(other.normals_);
        uv_ = std::move(other.uv_);
        shader_ = std::move(other.shader_);
        texture_data_ = std::move(other.texture_data_);
        texture_ = std::move(other.texture_);
        position_ = std::move(other.position_);
        rotation_ = std::move(other.rotation_);
        scale_ = std::move(other.scale_);

        return *this;
    }

    void Object::render(const RenderContext& context) const
    {
        render(context, texture_);
    }

    struct Transform
    {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };

    static inline glm::mat4 model_matrix(const Transform& trans)
    {
        const auto& [position, rotation, scale] = trans;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
        model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
        model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
        model = glm::scale(model, scale);

        return model;
    }

    void Object::render(const RenderContext& context, const Texture& tex) const
    {
        if (shader_ != nullptr)
        {
            auto render = with_shader(*shader_, [&, this](const auto& sh)
            {
                const auto& cam = context.camera;
                if (context.target)
                    glBindFramebuffer(GL_FRAMEBUFFER, *context.target);
                else
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                glm::mat4 model = model_matrix(
                    Transform{position_, rotation_, scale_}
                );

                sh.uniform("model") = model;
                sh.uniform("view") = cam.get_view();
                sh.uniform("projection") = cam.get_projection();
                sh.uniform("texture_sampler") = static_cast<int>(tex.get_unit() - GL_TEXTURE0);
                sh.uniform("time") = context.time;

                glBindVertexArray(vao_id_);
                glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
            });

            render();
        }
    }

    void Object::render(const RenderContext& context, const CubeMap&) const
    {
        if (shader_ != nullptr)
        {
            auto render = with_shader(*shader_, [&, this](const auto& sh)
            {
                const auto& cam = context.camera;

                if (context.target)
                    glBindFramebuffer(GL_FRAMEBUFFER, *context.target);
                else
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                glm::mat4 model = model_matrix(
                    Transform{position_, rotation_, scale_}
                );

                sh.uniform("model") = model;
                sh.uniform("view") = cam.get_view();
                sh.uniform("projection") = cam.get_projection();
                sh.uniform("reflectionMap") = static_cast<int>(GL_TEXTURE6 - GL_TEXTURE0);
                sh.uniform("cameraPos") = cam.get_position();

                glBindVertexArray(vao_id_);
                glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
            });

            render();
        }
    }
} // namespace pogl
