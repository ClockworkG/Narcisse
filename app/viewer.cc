#include <spdlog/spdlog.h>
#include <pogl/pogl.hh>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main(int argc, char** argv)
{
    if (!pogl::init_glut_context(pogl::GlutContextArguments(argc, argv)))
    {
        spdlog::error("Unable to init GL context");
        return EXIT_FAILURE;
    }

    try {
        auto scene = pogl::load_scene("scene.json");
        pogl::set_current_scene(scene);
    }
    catch (const std::runtime_error& err)
    {
        spdlog::error("{0}", err.what());
        return EXIT_FAILURE;
    }

    pogl::run_opengl();

    return EXIT_SUCCESS;
}
