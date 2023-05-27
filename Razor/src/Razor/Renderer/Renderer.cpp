#include "rzr_pch.h"

#include "Renderer.h"

namespace Razor
{
    Renderer::Renderer()
    {
    
    }

#if (RENDER_API == OPENGL_RENDER_API)

    void Renderer::CreateVertexArray()
    {
        m_VertexArray = std::make_unique<OpenGLVertexArray>();
    }

    void Renderer::CreateVertexBuffer(float* Vertices, uint32_t size)
    {
        m_VertexArray->AddVertexBuffer(std::make_shared<OpenGLVertexBuffer>(Vertices, size));
    }

    void Renderer::CreateIndexBuffer(uint32_t* Indices, uint32_t size)
    {
        m_VertexArray->SetIndexBuffer(std::make_shared<OpenGLIndexBuffer>(Indices, size));
    }

#elif (RENDER_API == VULKAN_RENDER_API)

#endif /* RENDER_API SWITCH */
}