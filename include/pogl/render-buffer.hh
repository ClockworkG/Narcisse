#pragma once

#include <GL/glew.h>

namespace pogl
{
    constexpr GLuint INVALID_RENDER_BUFFER = 0;

    class RenderBuffer
    {
    public:
        RenderBuffer(unsigned int width, unsigned int height);
        ~RenderBuffer();
        RenderBuffer(RenderBuffer&&);
        RenderBuffer& operator=(RenderBuffer&&);

        RenderBuffer(const RenderBuffer&) = delete;
        RenderBuffer& operator=(const RenderBuffer&) = delete;

        operator GLuint() const noexcept;

    private:
        GLuint buffer_id_ = INVALID_RENDER_BUFFER;
    };
} // namespace pogl
