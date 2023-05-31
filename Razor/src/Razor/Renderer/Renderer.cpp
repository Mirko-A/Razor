#include "rzr_pch.h"
#include "Renderer.h"

#include "Scene.h"

namespace Razor
{
    void Renderer::BeginScene(const std::shared_ptr<OrthographicCamera>& Camera)
    {
        Scene::GetSceneData()->ProjectionViewMatrix = Camera->GetProjectionViewMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& VertexArray,
                          const std::shared_ptr<Shader>& Shader)
    {
        Shader->Bind();
        Shader->UploadUniform("u_ProjectionViewMatrix", Scene::GetSceneData()->ProjectionViewMatrix);

        VertexArray->Bind();
        RenderCommand::DrawIndexed(VertexArray);
    }
}