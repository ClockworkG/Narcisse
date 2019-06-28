#include <pogl/texture.hh>
#include <utility>

namespace pogl
{
    Texture::Texture(const Dimension& dim)
        : dimension_(dim)
    {
        glGenTextures(1, &texture_id_);

        glBindTexture(GL_TEXTURE_2D, texture_id_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     dimension_.width, dimension_.height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, INVALID_TEXTURE);
    }

    Texture::~Texture()
    {
        if (texture_id_ != INVALID_TEXTURE)
        {
            glDeleteTextures(1, &texture_id_);
            texture_id_ = INVALID_TEXTURE;
        }
    }

    Texture::Texture(Texture&& other)
        : dimension_(std::move(other.dimension_))
        , texture_id_(std::exchange(other.texture_id_, INVALID_TEXTURE))
    {}

    Texture& Texture::operator=(Texture&& other)
    {
        if (texture_id_ != INVALID_TEXTURE)
            glDeleteTextures(1, &texture_id_);

        texture_id_ = std::exchange(other.texture_id_, INVALID_TEXTURE);
        dimension_ = std::move(other.dimension_);

        return *this;
    }

    Texture::operator GLuint() const noexcept
    {
        return texture_id_;
    }
} // namespace pogl
