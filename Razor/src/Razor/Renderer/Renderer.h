#pragma once

#include "RenderCommand.h"

namespace Razor
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& VertexArray);
    };
}