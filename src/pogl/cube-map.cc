#include <pogl/cube-map.hh>
#include <pogl/legacy/image_io.hh>
#include <vector>
#include <sstream>

namespace pogl
{
    CubeMap::CubeMap()
    {
        glGenTextures(1, &cube_map_id_);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_id_);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        for (std::size_t i = 0; i < 6; i++)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, 2048, 2048, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, NULL);
        }

        //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    }

    CubeMap::CubeMap(const textures_t& faces)
    {
        glGenTextures(1, &cube_map_id_);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_id_);

        std::size_t i = 0;
        for (const auto& texture : faces)
        {
            tifo::rgb24_image image = texture;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, image.sx, image.sy, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, image.pixels);
            i++;
        }

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    CubeMap::~CubeMap()
    {
        if (cube_map_id_ != INVALID_CUBE_MAP_ID)
        {
            glDeleteTextures(1, &cube_map_id_);
            cube_map_id_ = INVALID_CUBE_MAP_ID;
        }
    }

    CubeMap::CubeMap(CubeMap&& other)
        : cube_map_id_(std::exchange(other.cube_map_id_, INVALID_CUBE_MAP_ID))
    {}

    CubeMap& CubeMap::operator=(CubeMap&& other)
    {
        if (cube_map_id_ != INVALID_CUBE_MAP_ID)
            glDeleteTextures(1, &cube_map_id_);

        cube_map_id_ = std::exchange(other.cube_map_id_, INVALID_CUBE_MAP_ID);

        return *this;
    }

    CubeMap::operator GLuint() const noexcept
    {
        return cube_map_id_;
    }

    void CubeMap::save(const std::string& name) const
    {
        std::stringstream ss;

        for (std::size_t i = 0; i < 6; i++)
        {
            GLubyte* pixels = new GLubyte[2048 * 2048 * 3];
            glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_id_);
            glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                          GL_RGB, GL_UNSIGNED_BYTE, pixels);
            tifo::rgb24_image image(2048, 2048);
            image.pixels = pixels;
            ss << name << "_" << i << ".tga";
            tifo::save_image(image, ss.str().c_str());
            ss.str("");
        }
    }
} // namespace pogl
