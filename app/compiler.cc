#include <pogl/shader.hh>
#include <pogl/context.hh>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

namespace ptree = boost::property_tree;

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

    try {
        ptree::ptree program_tree{};
        ptree::read_json(program_path, program_tree);
    }
    catch (const ptree::json_parser::json_parser_error& err)
    {
        spdlog::error("Syntax error: {0}", err.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
