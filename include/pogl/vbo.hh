#pragma once

#include <algorithm>
#include <initializer_list>
#include <vector>

#include <GL/glew.h>

namespace pogl
{
    constexpr GLuint INVALID_VBO = 0;

    template <typename T>
    class VBO
    {
    public:
        using value_type = T;
        using data_type = std::vector<T>;
        using iterator = typename data_type::iterator;
        using const_iterator = typename data_type::const_iterator;
        using size_type = std::size_t;

        VBO(size_type size, value_type default_init = value_type{});
        VBO(const std::initializer_list<T>& init);

        template <typename Iterator>
        VBO(Iterator begin, Iterator end);

        ~VBO();
        VBO(VBO&&);
        VBO& operator=(VBO&&);

        VBO(const VBO&) = delete;
        VBO& operator=(const VBO&) = delete;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        size_type size() const noexcept;

    private:
        GLuint vbo_id_ = INVALID_VBO;
        data_type data_;

        void init_vbo_();
    };
} // namespace pogl

#include <pogl/vbo.hxx>
