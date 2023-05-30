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
    };
}