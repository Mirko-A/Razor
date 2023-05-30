#include "rzr_pch.h"

#include "RendererAPI.h"

namespace Razor
{
    RendererAPI::RendererAPI()
    {
    
    }

#if (RENDERER_API == OPENGL_RENDERER_API)

    /********* Creating data structures implementation *************************/
    std::shared_ptr<OpenGLVertexArray> RendererAPI::CreateVertexArray()
    {
        return std::make_shared<OpenGLVertexArray>();
    }

    std::shared_ptr<OpenGLVertexBuffer> RendererAPI::CreateVertexBuffer(float* Vertices, uint32_t size)
    {
        return std::make_shared<OpenGLVertexBuffer>(Vertices, size);
    }
    std::shared_ptr<OpenGLVertexBuffer> RendererAPI::CreateVertexBuffer(float* Vertices, uint32_t size, const BufferLayout& Layout)
    {
        std::shared_ptr<OpenGLVertexBuffer> VertexBuffer = CreateVertexBuffer(Vertices, size);
        VertexBuffer->SetLayout(Layout);

        return VertexBuffer;
    }

    std::shared_ptr<OpenGLIndexBuffer> RendererAPI::CreateIndexBuffer(uint32_t* Indices, uint32_t size)
    {
        return std::make_shared<OpenGLIndexBuffer>(Indices, size);
    }

    /********* Renderer commands implementation *************************/
    void RendererAPI::SetClearColor(const glm::vec4& ClearColor)
    {
        glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w);
    }

    void RendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray)
    {
        glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

#elif (RENDER_API == VULKAN_RENDERER_API)

#endif /* RENDER_API SWITCH */
}