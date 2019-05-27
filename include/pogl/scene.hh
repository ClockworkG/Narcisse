#pragma once

#include <GL/glew.h>

namespace pogl
{
    class Scene
    {
        friend Scene* get_scene();

    public:
        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = delete;

        void run() const;

    private:
        Scene() = default;
        static Scene* instance();
        static void display();

        void display_() const;
    };

    Scene* get_scene();
} // namespace pogl
