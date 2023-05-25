#pragma once

#include "Razor/Renderer/Buffer.h"

namespace Razor
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* Vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetData(float* Vertices, uint32_t size) override;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* Indices, uint32_t size);
        ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetData(uint32_t* Indices, uint32_t size) override;
    };
}