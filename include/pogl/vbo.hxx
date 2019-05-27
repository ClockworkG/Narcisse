#pragma once

#include <pogl/vbo.hh>

namespace pogl
{
    template <typename T>
    template <typename Iterator>
    VBO<T>::VBO(Iterator begin, Iterator end)
        : glGenBuffers(1, &vbo_id_)
        , data_(std::distance(begin, end))
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

        std::copy(begin, end, std::begin(data_));

        auto size = data_.size();
        glBufferData(GL_ARRAY_BUFFER,
                     size * sizeof (T),
                     data_.data(),
                     GL_STATIC_DRAW);
    }

    template <typename T>
    VBO<T>::~VBO()
    {
        if (vbo_id_ != INVALID_VBO)
            glDeleteBuffers(1, &vbo_id_);

        vbo_id_ = INVALID_VBO;
    }

    template <typename T>
    VBO<T>::VBO(VBO&& other)
        : vbo_id_(std::exchange(other.vbo_id_, INVALID_VBO))
        , data_(std::move(other.data_))
    {}

    template <typename T>
    auto VBO<T>::operator=(VBO&& other) -> VBO&
    {
        if (vbo_id_ != INVALID_VBO)
            glDeleteBuffers(1, &vbo_id_);

        vbo_id_ = std::exchange(other.vbo_id_, INVALID_VBO);
        data_ = std::move(other.data_);

        return *this;
    }
} // namespace pogl
