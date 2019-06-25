#include <pogl/object.hh>
#include <glm/gtc/matrix_transform.hpp>

namespace pogl
{
    Object::Object(const Mesh& mesh, program_ptr_t shader)
        : vao_id_(INVALID_VAO)
        , vertices_(begin(mesh.vertices), end(mesh.vertices))
        , normals_(begin(mesh.normals), end(mesh.normals))
        , shader_(shader)
    {
        glGenVertexArrays(1, &vao_id_);
        glBindVertexArray(vao_id_);

        shader_->attrib("position") = vertices_;
        shader_->attrib("normal") = normals_;
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
        , shader_(std::move(other.shader_))
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
        shader_ = std::move(other.shader_);
        position_ = std::move(other.position_);
        rotation_ = std::move(other.rotation_);
        scale_ = std::move(other.scale_);

        return *this;
    }

    void Object::display(const Camera& cam) const
    {
        if (shader_ != nullptr)
        {
            glUseProgram(*shader_);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position_);
            model = glm::rotate(model, rotation_.x, glm::vec3(1, 0, 0));
            model = glm::rotate(model, rotation_.y, glm::vec3(0, 1, 0));
            model = glm::rotate(model, rotation_.y, glm::vec3(0, 0, 1));
            model = glm::scale(model, scale_);

            const glm::mat4 mvp = cam.get_projection() * cam.get_view() * model;

            const auto mvp_loc = glGetUniformLocation(*shader_, "mvp");
            glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));

            glBindVertexArray(vao_id_);
            glDrawArrays(GL_TRIANGLES, 0, vertices_.size());

            glUseProgram(0);
        }
    }
} // namespace pogl
