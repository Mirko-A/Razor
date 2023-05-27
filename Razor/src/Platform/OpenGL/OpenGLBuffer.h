#pragma once

#include "Razor/Renderer/Buffer.h"

#include "glad/glad.h"

namespace Razor
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* Vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetLayout(BufferLayout Layout) override;
        const BufferLayout& GetLayout() const override;

        void SetData(float* Vertices, uint32_t size) override;
        
    private:
        GLenum ShaderDataTypeToGLenum(ShaderDataType Type);
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