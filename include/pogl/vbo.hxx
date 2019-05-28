#pragma once

#include <pogl/vbo.hh>

namespace pogl
{
    template <typename T, typename Policy>
    VBO<T, Policy>::VBO(size_type size, value_type default_init)
        : vbo_id_(INVALID_VBO)
        , data_(size, default_init)
    {
        init_vbo_();
    }

    template <typename T, typename Policy>
    VBO<T, Policy>::VBO(const std::initializer_list<T>& init)
        : vbo_id_(INVALID_VBO)
        , data_(init)
    {
        init_vbo_();
    }

    template <typename T, typename Policy>
    template <typename Iterator>
    VBO<T, Policy>::VBO(Iterator begin, Iterator end)
        : vbo_id_(INVALID_VBO)
        , data_(Policy::size() * std::distance(begin, end))
    {
        Policy::copy(begin, end, std::begin(data_));
        init_vbo_();
    }

    template <typename T, typename Policy>
    VBO<T, Policy>::~VBO()
    {
        if (vbo_id_ != INVALID_VBO)
            glDeleteBuffers(1, &vbo_id_);

        vbo_id_ = INVALID_VBO;
    }

    template <typename T, typename Policy>
    VBO<T, Policy>::VBO(VBO&& other)
        : vbo_id_(std::exchange(other.vbo_id_, INVALID_VBO))
        , data_(std::move(other.data_))
    {}

    template <typename T, typename Policy>
    auto VBO<T, Policy>::operator=(VBO&& other) -> VBO&
    {
        if (vbo_id_ != INVALID_VBO)
            glDeleteBuffers(1, &vbo_id_);

        vbo_id_ = std::exchange(other.vbo_id_, INVALID_VBO);
        data_ = std::move(other.data_);

        return *this;
    }

    template <typename T, typename Policy>
    auto VBO<T, Policy>::begin() -> iterator
    {
        return std::begin(data_);
    }

    template <typename T, typename Policy>
    auto VBO<T, Policy>::end() -> iterator
    {
        return std::end(data_);
    }

    template <typename T, typename Policy>
    auto VBO<T, Policy>::begin() const -> const_iterator
    {
        return std::cbegin(data_);
    }

    template <typename T, typename Policy>
    auto VBO<T, Policy>::end() const -> const_iterator
    {
        return std::cend(data_);
    }

    template <typename T, typename Policy>
    auto VBO<T, Policy>::size() const noexcept -> size_type
    {
        return data_.size();
    }

    template <typename T, typename Policy>
    void VBO<T, Policy>::init_vbo_()
    {
        glGenBuffers(1, &vbo_id_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

        auto size = data_.size();
        glBufferData(GL_ARRAY_BUFFER,
                     size * sizeof (T),
                     data_.data(),
                     GL_STATIC_DRAW);
    }

    template <typename T, typename Policy>
    VBO<T, Policy>::operator GLuint() const noexcept
    {
        return vbo_id_;
    }
} // namespace pogl
