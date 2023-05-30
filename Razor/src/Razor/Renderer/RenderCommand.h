#pragma once

#include "RendererAPI.h"

namespace Razor
{
    class RenderCommand
    {
    public:
        /********* Creating data structures commands *************************/
        inline static std::shared_ptr<VertexArray> CreateVertexArray()
        {
            return s_RendererAPI->CreateVertexArray();
        }

        inline static std::shared_ptr<OpenGLVertexBuffer> CreateVertexBuffer(float* Vertices, uint32_t size)
        {
            return s_RendererAPI->CreateVertexBuffer(Vertices, size);
        }
        inline static std::shared_ptr<OpenGLVertexBuffer> CreateVertexBuffer(float* Vertices, uint32_t size, const BufferLayout& Layout)
        {
            return s_RendererAPI->CreateVertexBuffer(Vertices, size, Layout);
        }

        inline static std::shared_ptr<OpenGLIndexBuffer> CreateIndexBuffer(uint32_t* Indices, uint32_t size)
        {
            return s_RendererAPI->CreateIndexBuffer(Indices, size);
        }

        /********* Renderer commands *************************/
        inline static void SetClearColor(const glm::vec4& ClearColor)
        {
            s_RendererAPI->SetClearColor(ClearColor);
        }

        inline static void Clear()
        {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray)
        {
            s_RendererAPI->DrawIndexed(VertexArray);
        }

    private:
        static RendererAPI* s_RendererAPI;
    };
}