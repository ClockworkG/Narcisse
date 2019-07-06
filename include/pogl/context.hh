#pragma once

#include <map>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <pogl/program.hh>

namespace pogl
{
    struct GlutVersion
    {
        uint8_t major = 4;
        uint8_t minor = 5;
    };

    struct GlutCliArgs
    {
        int argc;
        char** argv;
    };

    struct GlutWindowSize
    {
        unsigned short width = 500;
        unsigned short height = 500;
    };

    struct GlutContextArguments
    {
        GlutContextArguments(int argc, char** argv)
            : cli_args{argc, argv}
        {}

        GlutCliArgs     cli_args;
        GlutVersion     version;
        GlutWindowSize  window_size;

        unsigned int    display_mode = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
        unsigned int    context_profile = GLUT_CORE_PROFILE;

        const char*     window_name = "Default window";
    };

    bool init_glut_context(const GlutContextArguments& args);
    program_ptr_t get_shader(const std::string& name);
    void set_shader(const std::string& name, program_ptr_t shader);
} // namespace pogl
