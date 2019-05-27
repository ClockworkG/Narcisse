#include <pogl/context.hh>

namespace pogl
{
    bool init_glut_context(const GlutContextArguments& args)
    {
        auto [argc, argv] = args.cli_args;
        glutInit(&argc, argv);

        auto [major, minor] = args.version;
        glutInitContextVersion(major, minor);

        glutInitContextProfile(args.context_profile);
        glutInitDisplayMode(args.display_mode);

        auto [width, height] = args.window_size;
        glutInitWindowSize(width, height);

        glutCreateWindow(args.window_name);

        if (glewInit())
            return false;

        return true;
    }
} // namespace pogl
