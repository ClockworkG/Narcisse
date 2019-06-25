#include <fstream>

#include <pogl/scene.hh>
#include <pogl/context.hh>
#include <pogl/detail/scene-reader.hh>

#include <nlohmann/json.hpp>

#include <GL/freeglut.h>

using json = nlohmann::json;

namespace pogl
{
    Scene::Scene(SceneSettings&& settings)
        : settings_(std::move(settings))
    {
        const auto& background = settings_.background;
        glClearColor(background.x, background.y, background.z, 1.0);
    }

    void Scene::add_object(Object&& object)
    {
        objects_.push_back(std::move(object));
    }

    void Scene::display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const auto& obj : objects_)
            obj.display(settings_.camera);

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

        return scene;
    }

    void run_opengl()
    {
        glutSpecialFunc(
            [](int key, int x, int y)
            {
                switch (key)
                {
                case GLUT_KEY_F5:
                    set_current_scene(load_scene("scene.json"));
                    break;
                };
            }
        );
        glutDisplayFunc(
            []()
            {
                if (Scene::current_scene != nullptr)
                    Scene::current_scene->display();

                glutPostRedisplay();
            }
        );
        glutMainLoop();
    }
} // namespace pogl
