#include <pogl/scene.hh>

#include <GL/freeglut.h>

namespace pogl
{
    void Scene::run() const
    {
        glutDisplayFunc(Scene::display);
        glutMainLoop();
    }

    void Scene::display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        instance()->display_();
        glutSwapBuffers();
    }

    void Scene::display_() const
    {
    }

    Scene* Scene::instance()
    {
        static Scene the_scene;
        return &the_scene;
    }

    Scene* get_scene()
    {
        return Scene::instance();
    }
} // namespace pogl
