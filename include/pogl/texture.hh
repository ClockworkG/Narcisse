#pragma once

#include <GL/glew.h>
#include <pogl/legacy/image.hh>

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

        Texture() = default;
        Texture(const Dimension& dim, uint8_t* pixels = NULL);
        ~Texture();
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        operator GLuint() const noexcept;
        operator tifo::rgb24_image() const;

        GLuint get_unit() const noexcept;

        bool save(const char* filename) const;

    private:
        static inline GLuint texture_unit_ = GL_TEXTURE0;

        Dimension dimension_ = Dimension{0, 0};
        GLuint texture_id_ = INVALID_TEXTURE;
        GLuint unit_ = GL_TEXTURE0;
    };
} // namespace pogl
