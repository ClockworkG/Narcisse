#include <spdlog/spdlog.h>
#include <pogl/pogl.hh>

int main(int argc, char** argv)
{
    if (!pogl::init_glut_context(pogl::GlutContextArguments(argc, argv)))
    {
        spdlog::error("Unable to init GL context");
        return EXIT_FAILURE;
    }

    auto scene = pogl::get_scene();
    scene->run();

    return EXIT_SUCCESS;
}
