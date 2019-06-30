#pragma once

#include <filesystem>
#include <vector>

#include <glm/glm.hpp>

namespace fs = std::filesystem;

namespace pogl
{
    struct Mesh
    {
        Mesh() = default;
        ~Mesh() = default;
        Mesh(Mesh&&) = default;
        Mesh& operator=(Mesh&&) = default;
        Mesh(const Mesh&) = default;
        Mesh& operator=(const Mesh&) = default;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uv;
    };

    Mesh make_mesh(const fs::path& obj_path);
} // namespace pogl
