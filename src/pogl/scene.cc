#include <fstream>

#include <pogl/scene.hh>
#include <pogl/scene-reader.hh>

#include <nlohmann/json.hpp>

#include <GL/freeglut.h>

using json = nlohmann::json;

namespace pogl
{
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

        auto scene = std::make_shared<Scene>();

        if (json_handler.contains("camera"))
            scene->camera_ = read_scene<Camera>(json_handler["camera"]);

        return scene;
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
