#pragma once

#include "Razor/Renderer/Buffer.h"

namespace Razor
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> VertexBuffer) = 0;
        virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> IndexBuffer) = 0;

        inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const
        {
            return m_VertexBuffers;
        }

        inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const
        {
            return m_IndexBuffer;
        }

    protected:
        uint32_t m_VertexArrayID;

        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}