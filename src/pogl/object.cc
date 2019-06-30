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
//        shader_->attrib("normal") = normals_;
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
        if (shader_ != nullptr)
        {
            const auto& cam = context.camera;

            glUseProgram(*shader_);

            if (context.target)
                glBindFramebuffer(GL_FRAMEBUFFER, *context.target);
            else
                glBindFramebuffer(GL_FRAMEBUFFER, 0);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position_);
            model = glm::rotate(model, rotation_.x, glm::vec3(1, 0, 0));
            model = glm::rotate(model, rotation_.y, glm::vec3(0, 1, 0));
            model = glm::rotate(model, rotation_.z, glm::vec3(0, 0, 1));
            model = glm::scale(model, scale_);

            const glm::mat4 mvp = cam.get_projection() * cam.get_view() * model;

            const auto mvp_loc = glGetUniformLocation(*shader_, "mvp");
            glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));

            const auto tex_loc = glGetUniformLocation(*shader_, "texture_sampler");
            glUniform1i(tex_loc, texture_.get_unit() - GL_TEXTURE0);

            glBindVertexArray(vao_id_);
            glDrawArrays(GL_TRIANGLES, 0, vertices_.size());

            glUseProgram(0);
        }
    }
} // namespace pogl
