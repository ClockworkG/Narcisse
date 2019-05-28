#include <pogl/object.hh>

namespace pogl
{
    Object::Object(VBO<float>&& vertices, program_ptr_t program)
        : vao_id_(INVALID_VAO)
        , vertices_(std::move(vertices))
        , program_(program)
    {
        glGenVertexArrays(1, &vao_id_);
        glBindVertexArray(vao_id_);
        glBindBuffer(GL_ARRAY_BUFFER, vertices_);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);
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
        , program_(std::move(other.program_))
    {}

    Object& Object::operator=(Object&& other)
    {
        if (vao_id_ != INVALID_VAO)
            glDeleteVertexArrays(1, &vao_id_);

        vao_id_ = std::exchange(other.vao_id_, INVALID_VAO);
        vertices_ = std::move(other.vertices_);
        program_ = std::move(other.program_);

        return *this;
    }

    void Object::operator()(const Camera& cam) const
    {
        if (program_)
        {
            glUseProgram(*program_);
            auto view_loc = glGetUniformLocation(*program_, "view");
            auto proj_loc = glGetUniformLocation(*program_, "proj");
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(cam.get_view()));
            glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam.get_projection()));
        }

        glBindVertexArray(vao_id_);
        glDrawArrays(GL_TRIANGLES, 0, vertices_.size() / 3);
        glUseProgram(0);
    }
} // namespace pogl
