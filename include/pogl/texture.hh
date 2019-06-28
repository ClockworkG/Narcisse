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

        Texture(const Dimension& dim);
        ~Texture();
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        operator GLuint() const noexcept;

    private:
        Dimension dimension_;
        GLuint texture_id_;
    };
} // namespace pogl
