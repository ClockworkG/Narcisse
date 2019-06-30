#pragma once

#include <GL/glew.h>

namespace pogl
{
    constexpr static GLuint INVALID_TEXTURE  = 0;

    class Texture
    {
    public:
        struct Dimension
        {
            unsigned int width;
            unsigned int height;
        };

        Texture(const Dimension& dim, uint8_t* pixels = NULL);
        ~Texture();
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        operator GLuint() const noexcept;

        GLuint get_unit() const noexcept;

    private:
        static inline GLuint texture_unit_ = GL_TEXTURE0;

        Dimension dimension_;
        GLuint texture_id_;
        GLuint unit_;
    };
} // namespace pogl
