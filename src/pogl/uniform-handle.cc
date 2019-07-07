#include <pogl/uniform-handle.hh>
#include <pogl/program.hh>

namespace pogl
{
    UniformHandle::UniformHandle(const Program& program, const std::string& name)
        : location_(glGetUniformLocation(program, name.c_str()))
        , name_(name)
    {}
} // namespace pogl
