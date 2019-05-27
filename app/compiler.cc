#include <map>

#include <pogl/shader.hh>
#include <pogl/program.hh>
#include <pogl/context.hh>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

namespace ptree = boost::property_tree;
namespace fs = std::filesystem;

template <typename Shader>
pogl::shader_t compile_shader(const fs::path& filename, pogl::Program& program)
{
    auto shader = pogl::make_shader<Shader>(filename);
    if (!shader)
        throw std::runtime_error{shader.error()};

    program.attach(shader);
    return shader;
}

using compile_function_t = std::function<pogl::shader_t(const fs::path&, pogl::Program&)>;
using compile_functions_map_t = std::map<std::string, compile_function_t>;

static inline compile_functions_map_t compile_functions_map =
{
    {"vertex", compile_shader<pogl::vertex_shader_t>},
    {"fragment", compile_shader<pogl::fragment_shader_t>}
};

int main(int argc, char** argv)
{
    CLI::App app{"OpenGL compiler"};
    pogl::init_glut_context(
        pogl::GlutContextArguments(argc, argv)
    );

    std::string program_path;
    app.add_option("-p,--program", program_path, "JSON program metadatas")
        ->required()
        ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    ptree::ptree program_tree{};
    try {
        ptree::read_json(program_path, program_tree);
    }
    catch (const ptree::json_parser::json_parser_error& err)
    {
        spdlog::error("Syntax error: {0}", err.what());
        return EXIT_FAILURE;
    }

    spdlog::info("Compiling {0}", program_path);

    pogl::Program program;
    bool success = true;

    std::vector<pogl::shader_t> shaders;
    for (const auto& [kind, value] : program_tree)
    {
        auto query = compile_functions_map.find(kind);

        if (query == end(compile_functions_map))
        {
            spdlog::warn("Unknown kind {0}", kind);
            continue;
        }

        const auto& [_, compile] = *query;

        for (const auto& [_, shader_path_prop] : value)
        {
            fs::path shader_path = shader_path_prop.get<std::string>("");

            if (!fs::exists(shader_path))
            {
                spdlog::error("File {0} does not exist", shader_path.c_str());
                success = false;
                continue;
            }

            try {
                spdlog::info("Compiling shader {0}", shader_path.c_str());

                auto shader = compile(shader_path, program);
                shaders.push_back(std::move(shader));
            }
            catch (const std::runtime_error& err)
            {
                spdlog::error("Failed to compile {0}", shader_path.c_str());
                spdlog::error("{0}", err.what());
                success = false;
                continue;
            }
        }
    }

    if (!success)
    {
        spdlog::error("Program linking incomplete due to previous errors");
        return EXIT_FAILURE;
    }

    if (!program())
    {
        spdlog::error("Could not link program");
        spdlog::error("{0}", program.error());
    }

    spdlog::info("Compilation successful");

    return EXIT_SUCCESS;
}
