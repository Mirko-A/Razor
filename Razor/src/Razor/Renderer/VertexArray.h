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
    };
}