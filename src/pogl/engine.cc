#include <pogl/engine.hh>
#include <pogl/render-target.hh>
#include <pogl/cube-map.hh>
#include <pogl/legacy/image_io.hh>

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
    }

    void Engine::update(float elapsed)
    {
        static float total_time = 0;
        total_time += elapsed;

        float dx = cos(total_time * 0.5);
        float dz = sin(total_time * 0.5);
        auto pos = current_scene_->get_camera().get_position();
        current_scene_->get_camera().set_position(
                glm::vec3(15 * dx, pos.y, 15 * dz)
        );

        glutPostRedisplay();
    }

    void Engine::prerender_reflection()
    {
        static GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        static std::vector<std::pair<std::string, glm::vec3>> directions
        {
            {"right", glm::vec3(1, 0, 0)},
            {"left", glm::vec3(-1, 0, 0)},
            {"top", glm::vec3(0, 1, 0)},
            {"bottom", glm::vec3(0, -1, 0)},
            {"front", glm::vec3(0, 0, 1)},
            {"back", glm::vec3(0, 0, -1)},
        };

        glViewport(0, 0, 2048, 2048);
        std::size_t index = 0;

        RenderTarget target;
        RenderBuffer depth_buffer(2048, 2048);

        target.set_depthbuffer(depth_buffer);

        for (const auto& [name, dir] : directions)
        {
            target.set_texture(reflection_map_, GL_TEXTURE_CUBE_MAP_POSITIVE_X + index);

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

            index++;
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

        auto reflecting = current_scene_->get_reflecting().get_object();
        for (const auto& object : *current_scene_)
        {
            if (reflecting != &object)
                object.render(render_context);
            else
                object.render(render_context, reflection_map_);
        }

        glutSwapBuffers();
    }

    void Engine::run()
    {
        prerender_reflection();
        glutMainLoop();
    }
} // namespace pogl
