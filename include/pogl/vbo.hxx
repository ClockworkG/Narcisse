#pragma once

#include <pogl/vbo.hh>

namespace pogl
{
    template <typename T>
    VBO<T>::VBO(size_type size, value_type default_init)
        : vbo_id_(INVALID_VBO)
        , data_(size, default_init)
    {
        init_vbo_();
    }

    template <typename T>
    template <typename U>
    VBO<T>::VBO(const std::initializer_list<U>& init)
        : vbo_id_(INVALID_VBO)
        , data_(FlattenPolicy<U>::size() * init.size())
    {
        FlattenPolicy<U>::copy(std::begin(init),
                               std::end(init), std::begin(data_));
        init_vbo_();
    }

    template <typename T>
    template <typename Iterator>
    VBO<T>::VBO(Iterator begin, Iterator end)
        : vbo_id_(INVALID_VBO)
        , data_(
            FlattenPolicy<
                typename std::iterator_traits<Iterator>::value_type
            >::size() * std::distance(begin, end)
        )
    {
        FlattenPolicy<
            typename std::iterator_traits<Iterator>::value_type
        >::copy(begin, end, std::begin(data_));
        init_vbo_();
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

    template <typename T>
    auto VBO<T>::begin() -> iterator
    {
        return std::begin(data_);
    }

    template <typename T>
    auto VBO<T>::end() -> iterator
    {
        return std::end(data_);
    }

    template <typename T>
    auto VBO<T>::begin() const -> const_iterator
    {
        return std::cbegin(data_);
    }

    template <typename T>
    auto VBO<T>::end() const -> const_iterator
    {
        return std::cend(data_);
    }

    template <typename T>
    auto VBO<T>::size() const noexcept -> size_type
    {
        return data_.size();
    }

    template <typename T>
    auto VBO<T>::operator[](size_type idx) const -> value_type
    {
        return data_[idx];
    }

    template <typename T>
    auto VBO<T>::operator[](size_type idx) -> value_type&
    {
        return data_[idx];
    }

    template <typename T>
    void VBO<T>::init_vbo_()
    {
        glGenBuffers(1, &vbo_id_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

        auto size = data_.size();
        glBufferData(GL_ARRAY_BUFFER,
                     size * sizeof (T),
                     data_.data(),
                     GL_STATIC_DRAW);
    }

    template <typename T>
    VBO<T>::operator GLuint() const noexcept
    {
        return vbo_id_;
    }
} // namespace pogl
