#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"

namespace Razor
{
    class Renderer
    {
    public:
        static void BeginScene(const std::shared_ptr<OrthographicCamera>& Camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& VertexArray, 
                           const std::shared_ptr<Shader>& Shader);
    };
}