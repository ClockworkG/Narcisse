#include <pogl/scene.hh>

#include <GL/freeglut.h>

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

    scene_ptr_t load_scene(const fs::path&)
    {
        return std::make_shared<Scene>();
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
