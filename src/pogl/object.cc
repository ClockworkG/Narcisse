#include <pogl/object.hh>

namespace pogl
{
    Object::Object(const Mesh& mesh)
        : vao_id_(INVALID_VAO)
        , vertices_(begin(mesh.vertices), end(mesh.vertices))
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
    {}

    Object& Object::operator=(Object&& other)
    {
        if (vao_id_ != INVALID_VAO)
            glDeleteVertexArrays(1, &vao_id_);

        vao_id_ = std::exchange(other.vao_id_, INVALID_VAO);
        vertices_ = std::move(other.vertices_);

        return *this;
    }

    void Object::display() const
    {
        glBindVertexArray(vao_id_);
        glDrawArrays(GL_TRIANGLES, 0, vertices_.size() / 3);
        glUseProgram(0);
    }
} // namespace pogl
