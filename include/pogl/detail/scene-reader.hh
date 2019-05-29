#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

using json = nlohmann::json;

namespace pogl::detail
{
    template <typename TargetType>
    TargetType read_scene(const json& scene);
} // namespace pogl::detail

#include <pogl/detail/scene-reader.hxx>
