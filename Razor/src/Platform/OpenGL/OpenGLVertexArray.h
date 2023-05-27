#pragma once

#include "Razor/Renderer/VertexArray.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Razor
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(std::shared_ptr<VertexBuffer> VertexBuffer) override;
        void SetIndexBuffer(std::shared_ptr<IndexBuffer> IndexBuffer) override;

        inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const
        {
            return m_VertexBuffers;
        }

        inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const
        {
            return m_IndexBuffer;
        }

    private:
        uint32_t m_VertexArrayID;

        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}