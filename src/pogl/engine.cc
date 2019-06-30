#include <pogl/engine.hh>
#include <pogl/render-target.hh>

#include <GL/freeglut.h>

#include <iostream>
#include <ctime>
#include <chrono>

namespace pogl
{
    Engine::Engine()
        : current_scene_(nullptr)
        , mirror_target_{}
        , mirror_texture_(Texture::Dimension{500, 500})
        , depth_buffer_(500, 500)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mirror_target_);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mirror_texture_, 0);

        glutDisplayFunc([]()
                {
                    Engine* engine = Engine::get_instance();
                    engine->render();
                }
        );
        glutIdleFunc([]()
                {
                    static auto timestamp = std::chrono::high_resolution_clock::now();

                    auto tmp_timestamp = std::chrono::high_resolution_clock::now();
                    float elapsed = std::chrono::duration<float>(tmp_timestamp - timestamp).count();
                    timestamp = tmp_timestamp;

                    Engine* engine = Engine::get_instance();
                    engine->update(elapsed);
                }
        );
        glViewport(0, 0, 500, 500);
    }

    void Engine::update(float elapsed)
    {
        static float total_time = 0;
        total_time += elapsed;

        float dx = cos(total_time);
        float dz = sin(total_time);
        auto pos = current_scene_->get_camera().get_position();
        current_scene_->get_camera().set_position(
                glm::vec3(15 * dx, pos.y, 15 * dz)
        );

        glutPostRedisplay();
    }

    void Engine::render()
    {
        static GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers);

        if (current_scene_ == nullptr)
            return;

        glBindFramebuffer(GL_FRAMEBUFFER, mirror_target_);
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
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

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.12f, 0.50f, 0.57f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto render_context = RenderContext
        {
            camera,
            nullptr
        };

        for (const auto& object : *current_scene_)
        {
            if (&object != reflecting.get_object())
                object.render(render_context);
        }

        reflecting.get_object()->render(render_context, mirror_texture_);

        glutSwapBuffers();
    }

    void Engine::run()
    {
        glutMainLoop();
    }
} // namespace pogl
