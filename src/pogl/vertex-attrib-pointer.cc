#include <pogl/vertex-attrib-pointer.hh>

#include <pogl/program.hh>

namespace pogl
{
    VertexAttribPointer::VertexAttribPointer(const Program& program,
                                             const std::string& name)
        : location_(glGetAttribLocation(program, name.c_str()))
    {}
} // namespace pogl
