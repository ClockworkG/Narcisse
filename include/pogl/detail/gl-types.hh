#pragma once

#include <boost/hana.hpp>

#include <GL/glew.h>

namespace hana = boost::hana;

namespace pogl
{
    constexpr inline auto gl_types = hana::make_map(
        hana::make_pair(hana::type_c<float>, GL_FLOAT)
    );
} // namespace pogl
