#pragma once

#include <boost/hana.hpp>
#include <pogl/detail/meta.hh>

namespace hana = boost::hana;

namespace pogl::detail
{
    template<>
    glm::vec3 read_scene<glm::vec3>(const json& scene)
    {
        glm::vec3 vec;

        for (std::size_t i = 0; i < 3; i++)
            vec[i] = scene[i].get<float>();

        return vec;
    }

    template<>
    float read_scene<float>(const json& scene)
    {
        return scene.get<float>();
    }

    template <typename T>
    void deserialize(const json& scene, T& object)
    {
        hana::for_each(hana::keys(object),
            [&object, &scene](const auto& key)
            {
                const char* c_key = key.c_str();
                if (!scene.contains(c_key))
                    return;

                auto& member = hana::at_key(object, key);
                using member_t = std::remove_reference_t<decltype(member)>;
                member = read_scene<member_t>(scene[c_key]);
            }
        );
    }

    template<>
    Camera read_scene<Camera>(const json& scene)
    {
        CameraSettings settings;
        deserialize(scene, settings);
        return Camera(std::move(settings));
    }

    template<>
    Object read_scene<Object>(const json& scene)
    {
        auto shader_name = scene["shader"];
        return Object(make_mesh(scene["mesh"]), get_shader(shader_name));
    }
} // namespace pogl::detail
