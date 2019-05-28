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
        std::for_each(begin(objects_), end(objects_),
                      [this](const auto& obj)
                      {
                          obj(camera_);
                      });
    }

    void Scene::add_object(Object&& obj)
    {
        objects_.push_back(std::move(obj));
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
