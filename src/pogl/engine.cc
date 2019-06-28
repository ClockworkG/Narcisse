#include <pogl/engine.hh>
#include <pogl/render-target.hh>

#include <GL/freeglut.h>

namespace pogl
{
    Engine::Engine()
    {
        glutIdleFunc(glutPostRedisplay);
        glutDisplayFunc([]()
                {
                    Engine* engine = Engine::get_instance();
                    engine->render();
                }
        );
    }

    void Engine::render()
    {
        if (current_scene_ == nullptr)
            return;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& reflecting = current_scene_->get_reflecting();
        const auto& camera = current_scene_->get_camera();

        auto context = RenderContext
        {
            reflecting.mirror_camera(camera),
            nullptr
        };

        for (const auto& object : *current_scene_)
        {
            if (&object != reflecting.get_object())
                object.render(context);
        }

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void Engine::run()
    {
        glutMainLoop();
    }
} // namespace pogl
