#pragma once

#include <array>

#include <pogl/texture.hh>

namespace pogl
{
    constexpr static inline GLuint INVALID_CUBE_MAP_ID = 0;

    class CubeMap
    {
    public:
        enum class Face
        {
            RIGHT = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            LEFT = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            TOP = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            BOTTOM = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            BACK = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            FRONT = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };

        using textures_t = std::array<Texture, 6>;

        CubeMap();
        CubeMap(const textures_t& faces);
        ~CubeMap();
        CubeMap(CubeMap&& other);
        CubeMap& operator=(CubeMap&& other);

        CubeMap(const CubeMap&) = delete;
        CubeMap& operator=(const CubeMap&) = delete;

        operator GLuint() const noexcept;

        void save(const std::string& name) const;

    private:
        GLuint cube_map_id_ = INVALID_CUBE_MAP_ID;
    };
} // namespace pogl
