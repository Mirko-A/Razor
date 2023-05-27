#pragma once

#include "Platform/OpenGL/OpenGLBuffer.h"

#include <memory>

namespace Razor
{
    class Renderer
    {
    public:
        Renderer();

#if (RENDER_API == OPENGL_RENDER_API)
        std::unique_ptr<OpenGLVertexBuffer> CreateVertexBuffer(float* Vertices, uint32_t size);
        std::unique_ptr<OpenGLIndexBuffer> CreateIndexBuffer(uint32_t* Indices, uint32_t size);
#elif (RENDER_API == VULKAN_RENDER_API)

#endif /* RENDER_API SWITCH */
    };
}