#pragma once

#include <pogl/vbo.hh>

namespace pogl
{
    template <typename T, unsigned int Stride>
    VBO<T, Stride>::VBO(size_type size, value_type default_init)
        : vbo_id_(INVALID_VBO)
        , data_(size, default_init)
    {
        init_vbo_();
    }

    template <typename T, unsigned int Stride>
    template <typename U>
    VBO<T, Stride>::VBO(const std::initializer_list<U>& init)
        : vbo_id_(INVALID_VBO)
        , data_(detail::FlattenPolicy<U>::size() * init.size())
    {
        detail::FlattenPolicy<U>::copy(std::begin(init),
                                       std::end(init), std::begin(data_));
        init_vbo_();
    }

    template <typename T, unsigned int Stride>
    template <typename Iterator>
    VBO<T, Stride>::VBO(Iterator begin, Iterator end)
        : vbo_id_(INVALID_VBO)
        , data_(
            detail::FlattenPolicy<
                typename std::iterator_traits<Iterator>::value_type
            >::size() * std::distance(begin, end)
        )
    {
        detail::FlattenPolicy<
            typename std::iterator_traits<Iterator>::value_type
        >::copy(begin, end, std::begin(data_));
        init_vbo_();
    }

    template <typename T, unsigned int Stride>
    VBO<T, Stride>::~VBO()
    {
        if (vbo_id_ != INVALID_VBO)
            glDeleteBuffers(1, &vbo_id_);

        vbo_id_ = INVALID_VBO;
    }

    template <typename T, unsigned int Stride>
    VBO<T, Stride>::VBO(VBO&& other)
        : vbo_id_(std::exchange(other.vbo_id_, INVALID_VBO))
        , data_(std::move(other.data_))
    {}

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::operator=(VBO&& other) -> VBO&
    {
        if (vbo_id_ != INVALID_VBO)
            glDeleteBuffers(1, &vbo_id_);

        vbo_id_ = std::exchange(other.vbo_id_, INVALID_VBO);
        data_ = std::move(other.data_);

        return *this;
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::begin() -> iterator
    {
        return std::begin(data_);
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::end() -> iterator
    {
        return std::end(data_);
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::begin() const -> const_iterator
    {
        return std::cbegin(data_);
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::end() const -> const_iterator
    {
        return std::cend(data_);
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::size() const noexcept -> size_type
    {
        return data_.size() / Stride;
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::real_size() const noexcept -> size_type
    {
        return data_.size();
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::operator[](size_type idx) const -> value_type
    {
        return data_[idx];
    }

    template <typename T, unsigned int Stride>
    auto VBO<T, Stride>::operator[](size_type idx) -> value_type&
    {
        return data_[idx];
    }

    template <typename T, unsigned int Stride>
    void VBO<T, Stride>::init_vbo_()
    {
        glGenBuffers(1, &vbo_id_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

        auto size = data_.size();
        glBufferData(GL_ARRAY_BUFFER,
                     size * sizeof (T),
                     data_.data(),
                     GL_STATIC_DRAW);
    }

    template <typename T, unsigned int Stride>
    VBO<T, Stride>::operator GLuint() const noexcept
    {
        return vbo_id_;
    }
} // namespace pogl
