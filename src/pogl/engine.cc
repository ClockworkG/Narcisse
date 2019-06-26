#include <pogl/engine.hh>

#include <GL/freeglut.h>

namespace pogl
{
    Engine::Engine()
    {
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

        auto context = RenderContext
        {
            current_scene_->get_camera()
        };

        // Render frame
        for (const auto& object : *current_scene_)
            object.render(context);

        glutSwapBuffers();
        glutPostRedisplay();
    }

    void Engine::run()
    {
        glutMainLoop();
    }
} // namespace pogl
