#include <pogl/texture.hh>
#include <pogl/legacy/image_io.hh>
#include <stdexcept>
#include <utility>

namespace pogl
{
    Texture::Texture(const Dimension& dim, uint8_t* pixels)
        : dimension_(dim)
        , unit_(texture_unit_++)
    {
        glGenTextures(1, &texture_id_);
        glActiveTexture(unit_);
        glBindTexture(GL_TEXTURE_2D, texture_id_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     dimension_.width, dimension_.height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
        , unit_(std::move(other.unit_))
    {}

    Texture& Texture::operator=(Texture&& other)
    {
        if (texture_id_ != INVALID_TEXTURE)
            glDeleteTextures(1, &texture_id_);

        texture_id_ = std::exchange(other.texture_id_, INVALID_TEXTURE);
        dimension_ = std::move(other.dimension_);
        unit_ = std::move(other.unit_);

        return *this;
    }

    Texture::operator GLuint() const noexcept
    {
        return texture_id_;
    }

    GLuint Texture::get_unit() const noexcept
    {
        return unit_;
    }

    bool Texture::save(const char* filename) const
    {
        GLubyte* pixels = new GLubyte[dimension_.width * dimension_.height * 3];
        glReadPixels(0, 0, dimension_.width, dimension_.height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        tifo::rgb24_image image(dimension_.width, dimension_.height);
        image.pixels = pixels;
        return tifo::save_image(image, filename);
    }
} // namespace pogl
