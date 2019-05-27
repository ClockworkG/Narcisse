#include <spdlog/spdlog.h>
#include <pogl/pogl.hh>

int main(int argc, char** argv)
{
    pogl::init_glut_context(
        pogl::GlutContextArguments(argc, argv)
    );

    pogl::Program program;
    std::ifstream binary("program.bin", std::ios_base::binary);

    binary >> program;

    return EXIT_SUCCESS;
}
