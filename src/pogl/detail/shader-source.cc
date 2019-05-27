#include <pogl/detail/shader-source.hh>

namespace pogl::detail
{
    ShaderSource::~ShaderSource()
    {
        for (int i = 0; i < count; i++)
            delete[] string[i];

        delete[] length;
        delete[] string;
    }
} // namespace pogl::detail
