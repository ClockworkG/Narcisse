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
    {
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

    void Engine::prerender_reflection()
    {
        static GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        static std::map<std::string, glm::vec3> directions
        {
            {"top", glm::vec3(0, 1, 0)},
            {"bottom", glm::vec3(0, -1, 0)},
            {"right", glm::vec3(1, 0, 0)},
            {"left", glm::vec3(-1, 0, 0)},
            {"front", glm::vec3(0, 0, 1)},
            {"back", glm::vec3(0, 0, -1)},
        };

        RenderTarget target;

        for (const auto& [name, dir] : directions)
        {
            RenderBuffer depth_buffer(500, 500);
            Texture texture(Texture::Dimension{500, 500});

            target.set_depthbuffer(depth_buffer);
            target.set_texture(texture);

            glDrawBuffers(1, DrawBuffers);

            glBindFramebuffer(GL_FRAMEBUFFER, target);
            glClearColor(0.1f, 0.1f, 0.1f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            auto reflecting = current_scene_->get_reflecting();
            auto render_context = RenderContext
            {
                reflecting.mirror_camera(dir),
                    &target
            };

            for (const auto& object : *current_scene_)
            {
                if (&object == reflecting.get_object())
                    continue;

                object.render(render_context);
            }

            texture.save((std::string(name) + ".tga").c_str());
        }
    }

    void Engine::render()
    {
        if (current_scene_ == nullptr)
            return;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto render_context = RenderContext
        {
            current_scene_->get_camera(),
            nullptr
        };

        for (const auto& object : *current_scene_)
            object.render(render_context);

        glutSwapBuffers();
    }

    void Engine::run()
    {
        prerender_reflection();
        glutMainLoop();
    }
} // namespace pogl
