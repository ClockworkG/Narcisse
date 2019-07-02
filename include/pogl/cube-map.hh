#pragma once

#include <array>

#include <pogl/texture.hh>

namespace pogl
{
    constexpr static inline GLuint INVALID_CUBE_MAP_ID = 0;

    class CubeMap
    {
    public:
        using textures_t = std::array<Texture, 6>;

        CubeMap() = default;
        CubeMap(const textures_t& faces);
        ~CubeMap();
        CubeMap(CubeMap&& other);
        CubeMap& operator=(CubeMap&& other);

        CubeMap(const CubeMap&) = delete;
        CubeMap& operator=(const CubeMap&) = delete;

        operator GLuint() const noexcept;

    private:
        GLuint cube_map_id_ = INVALID_CUBE_MAP_ID;
    };
} // namespace pogl
