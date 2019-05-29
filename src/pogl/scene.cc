#include <fstream>

#include <pogl/scene.hh>
#include <pogl/scene-reader.hh>

#include <nlohmann/json.hpp>

#include <GL/freeglut.h>

using json = nlohmann::json;

namespace pogl
{
    Scene::Scene(SceneSettings settings)
        : settings_(settings)
    {}

    void Scene::display() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutSwapBuffers();
    }

    void set_current_scene(scene_ptr_t scene)
    {
        Scene::current_scene = scene;
    }

    scene_ptr_t load_scene(const fs::path& scene_path)
    {
        std::ifstream is{scene_path};
        if (!is)
            return nullptr;

        json json_handler;
        is >> json_handler;

        SceneSettings scene_settings;
        deserialize(json_handler, scene_settings);
        return std::make_shared<Scene>(scene_settings);
    }

    void run_opengl()
    {
        glutDisplayFunc(
            []()
            {
                if (Scene::current_scene != nullptr)
                    Scene::current_scene->display();
            }
        );
        glutMainLoop();
    }
} // namespace pogl
