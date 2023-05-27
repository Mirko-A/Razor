#pragma once

#if (RENDER_API == OPENGL_RENDER_API)

#include "glad/glad.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#else

#endif

#include <memory>

namespace Razor
{
    class Renderer
    {
    public:
        Renderer();

        void CreateVertexArray();
        void CreateVertexBuffer(float* Vertices, uint32_t size);
        void CreateIndexBuffer(uint32_t* Indices, uint32_t size);

#if (RENDER_API == OPENGL_RENDER_API)
        inline const std::unique_ptr<OpenGLVertexArray>& GetVertexArray()
        {
            return m_VertexArray;
        }

    private:
        std::unique_ptr<OpenGLVertexArray> m_VertexArray;
#elif (RENDER_API == VULKAN_RENDER_API)

#endif /* RENDER_API SWITCH */
    };
}