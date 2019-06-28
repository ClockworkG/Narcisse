#include <pogl/engine.hh>
#include <pogl/render-target.hh>

#include <GL/freeglut.h>

#include <iostream>

namespace pogl
{
    Engine::Engine()
        : current_scene_(nullptr)
        , mirror_target_{}
        , mirror_texture_(Texture::Dimension{500, 500})
        , depth_buffer_(500, 500)
    {
        //glutIdleFunc(glutPostRedisplay);
        glutDisplayFunc([]()
                {
                    Engine* engine = Engine::get_instance();
                    engine->render();
                }
        );

        glBindFramebuffer(GL_FRAMEBUFFER, mirror_target_);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mirror_texture_, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, INVALID_FRAME_BUFFER);
    }

    void Engine::render()
    {
        if (current_scene_ == nullptr)
            return;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto& reflecting = current_scene_->get_reflecting();
        const auto& camera = current_scene_->get_camera();

        auto mirror_context = RenderContext
        {
            reflecting.mirror_camera(camera),
            &mirror_target_
        };

        for (const auto& object : *current_scene_)
        {
            if (&object != reflecting.get_object())
                object.render(mirror_context);
        }

        auto render_context = RenderContext
        {
            camera,
            nullptr
        };

        for (const auto& object : *current_scene_)
            object.render(render_context);

        glutSwapBuffers();
    }

    void Engine::run()
    {
        glutMainLoop();
    }
} // namespace pogl
