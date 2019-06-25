#include <pogl/object.hh>

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
    {}

    Object& Object::operator=(Object&& other)
    {
        if (vao_id_ != INVALID_VAO)
            glDeleteVertexArrays(1, &vao_id_);

        vao_id_ = std::exchange(other.vao_id_, INVALID_VAO);
        vertices_ = std::move(other.vertices_);
        normals_ = std::move(other.normals_);
        shader_ = std::move(other.shader_);

        return *this;
    }

    void Object::display(const Camera& cam) const
    {
        if (shader_ != nullptr)
        {
            glUseProgram(*shader_);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            auto view_loc = glGetUniformLocation(*shader_, "view");
            auto proj_loc = glGetUniformLocation(*shader_, "proj");
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(cam.get_view()));
            glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam.get_projection()));
            glBindVertexArray(vao_id_);
            glDrawArrays(GL_TRIANGLES, 0, vertices_.size());

            glUseProgram(0);
        }
    }
} // namespace pogl
