#pragma once

#if (RENDERER_API == OPENGL_RENDERER_API)

#include "glad/glad.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#else

#endif

#include "glm/glm.hpp"

#include <memory>

namespace Razor
{
    class RendererAPI
    {
    public:
        RendererAPI();

#if (RENDERER_API == OPENGL_RENDERER_API)

        /********* Creating data structures *************************/
        std::shared_ptr<OpenGLVertexArray> CreateVertexArray();
        std::shared_ptr<OpenGLVertexBuffer> CreateVertexBuffer(float* Vertices, uint32_t size);
        std::shared_ptr<OpenGLVertexBuffer> CreateVertexBuffer(float* Vertices, uint32_t size, const BufferLayout& Layout);
        std::shared_ptr<OpenGLIndexBuffer> CreateIndexBuffer(uint32_t* Indices, uint32_t size);

        /********* Renderer commands *************************/
        void SetClearColor(const glm::vec4& ClearColor);
        void Clear();

        void DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray);

#elif (RENDER_API == VULKAN_RENDER_API)

#endif /* RENDER_API SWITCH */
    };
}