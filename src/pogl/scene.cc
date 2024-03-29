#include <fstream>

#include <pogl/scene.hh>
#include <pogl/context.hh>
#include <pogl/detail/scene-reader.hh>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace pogl
{
    Scene::Scene(SceneSettings&& settings)
        : settings_(std::move(settings))
        , reflecting_{}
    {
        const auto& background = settings_.background;
        glClearColor(background.x, background.y, background.z, 1.0);
    }

    void Scene::add_object(Object&& object, bool reflecting)
    {
        objects_.push_back(std::move(object));

        if (reflecting)
            reflecting_.set_object(&objects_.back());
    }

    scene_ptr_t load_scene(const fs::path& scene_path)
    {
        std::ifstream is{scene_path};
        if (!is)
            return nullptr;

        json json_handler;
        is >> json_handler;

        SceneSettings scene_settings;
        detail::deserialize(json_handler["scene"], scene_settings);

        auto scene = std::make_shared<Scene>(std::move(scene_settings));

        for (const auto& [key, value] : json_handler["shaders"].items())
        {
            std::string vertex_path = value[0];
            std::string fragment_path = value[1];
            set_shader(key, make_program(vertex_path, fragment_path));
        }

        if (json_handler["scene"].contains("objects"))
        {
            for (const auto& obj : json_handler["scene"]["objects"])
                scene->add_object(detail::read_scene<Object>(obj));
        }

        if (json_handler["scene"].contains("reflecting"))
            scene->add_object(detail::read_scene<Object>(json_handler["scene"]["reflecting"]), true);

        return scene;
    }
} // namespace pogl
