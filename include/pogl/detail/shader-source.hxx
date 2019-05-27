#pragma once

#include <algorithm>
#include <boost/algorithm/string.hpp>

namespace pogl::detail
{
    template <typename Iterator>
    ShaderSource make_shader_source(Iterator begin, Iterator end)
    {
        const int size = std::distance(begin, end);
        auto strings = new GLchar*[size];
        auto lengths = new GLint[size];

        for (auto [line, idx] = std::make_pair(begin, 0); line != end; line++, idx++)
        {
            const std::size_t line_size = line->size();

            lengths[idx] = line_size;

            strings[idx] = new GLchar[line_size + 1];
            strings[idx][line_size] = '\0';
            std::memcpy(
                strings[idx], line->c_str(),
                line_size
            );
        }

        return ShaderSource{size, strings, lengths};
    }

    inline ShaderSource make_shader_source(const std::string& source)
    {
        std::vector<std::string> lines;
        boost::split(lines, source, boost::is_any_of("\n"));
        return make_shader_source(
            std::begin(lines), std::end(lines)
        );
    }
} // namespace pogl::detail
