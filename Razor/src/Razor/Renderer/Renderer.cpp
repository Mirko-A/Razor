#include "rzr_pch.h"
#include "Renderer.h"

namespace Razor
{
    void Renderer::BeginScene()
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& VertexArray)
    {
        VertexArray->Bind();
        RenderCommand::DrawIndexed(VertexArray);
    }
}