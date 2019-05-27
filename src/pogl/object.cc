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
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertices_);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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

    void Object::operator()() const
    {
        if (program_)
            glUseProgram(*program_);

        glBindVertexArray(vao_id_);
        glDrawArrays(GL_TRIANGLES, 0, vertices_.size() / 3);
        glUseProgram(0);
    }
} // namespace pogl
