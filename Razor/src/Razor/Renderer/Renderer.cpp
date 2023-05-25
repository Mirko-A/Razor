#include "rzr_pch.h"

#include "Renderer.h"

namespace Razor
{
    Renderer::Renderer()
    {
    
    }
    
#if (RENDER_API == OPENGL_RENDER_API)
    std::unique_ptr<OpenGLVertexBuffer> Renderer::CreateVertexBuffer(float* Vertices, uint32_t size)
    {
        return std::make_unique<OpenGLVertexBuffer>(Vertices, size);
    }

    std::unique_ptr<OpenGLIndexBuffer> Renderer::CreateIndexBuffer(uint32_t* Indices, uint32_t size)
    {
        return std::make_unique<OpenGLIndexBuffer>(Indices, size);
    }
#elif (RENDER_API == VULKAN_RENDER_API

#endif /* RENDER_API SWITCH */
}