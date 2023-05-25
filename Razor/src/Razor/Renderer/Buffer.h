#pragma once

#include <cstdint>

namespace Razor
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(float* Vertices, uint32_t size) = 0;

        inline uint32_t GetID() const
        {
            return m_BufferID;
        }

    protected:
        uint32_t m_BufferID;
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(uint32_t* Indices, uint32_t size) = 0;

        inline uint32_t GetID() const
        {
            return m_BufferID;
        }

    protected:
        uint32_t m_BufferID;
    };
}