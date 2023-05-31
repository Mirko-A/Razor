#include "Razor.h"

#define VERTEX_COUNT (4)
#define INDEX_COUNT  (6)

float vertices[VERTEX_COUNT * (3 + 4)] =
{
     -0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      0.3f,  0.3f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     -0.3f,  0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
};

Razor::BufferLayout Layout =
{
    { Razor::ShaderDataType::Float3, "vs_Position"},
    { Razor::ShaderDataType::Float4, "vs_Color"},
};

uint32_t indices[INDEX_COUNT] =
{
    0, 1, 3,
    3, 1, 2,
};

// SANDBOX APPLICATION IS CREATED HERE
class TestLayer : public Razor::Layer
{
public:
    TestLayer(const std::string& Name = "Test layer")
    {
        std::ifstream SourceFile;
        std::stringstream VertexSourceStringStream;
        std::stringstream FragmentSourceStringStream;

        SourceFile.open("VertexSource.txt", std::ios::in);
        RZR_CORE_ASSERT(SourceFile.is_open(), "Failed to load Vertex Shader source file!");
        VertexSourceStringStream << SourceFile.rdbuf();
        SourceFile.close();

        SourceFile.open("FragmentSource.txt", std::ios::in);
        RZR_CORE_ASSERT(SourceFile.is_open(), "Failed to load Fragment  Shader source file!");
        FragmentSourceStringStream << SourceFile.rdbuf();
        SourceFile.close();

        m_VertexArray = Razor::RenderCommand::CreateVertexArray();
        m_VertexArray->AddVertexBuffer(Razor::RenderCommand::CreateVertexBuffer(vertices, sizeof(vertices), Layout));
        m_VertexArray->SetIndexBuffer(Razor::RenderCommand::CreateIndexBuffer(indices, sizeof(indices)));

        m_Shader = std::make_shared<Razor::Shader>(VertexSourceStringStream.str(), FragmentSourceStringStream.str());
        m_OrthoCamera = std::make_shared<Razor::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);
    }

    void OnUpdate()
    {
        if (Razor::Input::IsKeyPressed(RZR_KEY_LEFT))
        {
            m_CameraPosition.x -= m_CameraSpeed;
            m_OrthoCamera->SetPosition(m_CameraPosition);
        }
        else if (Razor::Input::IsKeyPressed(RZR_KEY_RIGHT))
        {
            m_CameraPosition.x += m_CameraSpeed;
            m_OrthoCamera->SetPosition(m_CameraPosition);
        }

        if (Razor::Input::IsKeyPressed(RZR_KEY_UP))
        {
            m_CameraPosition.y += m_CameraSpeed;
            m_OrthoCamera->SetPosition(m_CameraPosition);
        }
        else if (Razor::Input::IsKeyPressed(RZR_KEY_DOWN))
        {
            m_CameraPosition.y -= m_CameraSpeed;
            m_OrthoCamera->SetPosition(m_CameraPosition);
        }

        if (Razor::Input::IsKeyPressed(RZR_KEY_A))
        {
            m_CameraRotation += m_CameraSpeed;
            m_OrthoCamera->SetRotation(m_CameraRotation);
        }
        else if (Razor::Input::IsKeyPressed(RZR_KEY_D))
        {
            m_CameraRotation -= m_CameraSpeed;
            m_OrthoCamera->SetRotation(m_CameraRotation);
        }

        if (Razor::Input::IsKeyPressed(RZR_KEY_S))
        {
            m_OrthoCamera->Zoom(Razor::OrthographicCamera::ZoomDirection::ZOOM_OUT, m_CameraSpeed);
        }
        else if (Razor::Input::IsKeyPressed(RZR_KEY_W))
        {
            m_OrthoCamera->Zoom(Razor::OrthographicCamera::ZoomDirection::ZOOM_IN, m_CameraSpeed);
        }

        Razor::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Razor::RenderCommand::Clear();

        Razor::Renderer::BeginScene(m_OrthoCamera);

        for (const auto& VBO : m_VertexArray->GetVertexBuffers())
        {
            VBO->SetData(vertices, sizeof(vertices));

            Razor::Renderer::Submit(m_VertexArray, m_Shader);
        }

        Razor::Renderer::EndScene();
    }

    void OnEvent(Razor::Event& e)
    {
        Razor::EventDispatcher EvDispatcher(e);
        EvDispatcher.Dispatch<Razor::KeyPressedEvent>(BIND_FN(TestLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(Razor::KeyPressedEvent& e)
    {
        // RZR_INFO("KEY {0} PRESSED", (char)e.GetKeyCode());

        return false;
    }

    void RenderImGui()
    {
        ImGui::Begin("Cube editor");
        ImGui::SliderFloat("V0 X", &vertices[7 * 0], -1.0f, 1.0f);
        ImGui::SliderFloat("V0 Y", &vertices[7 * 0 + 1],  -1.0f, 1.0f);

        ImGui::SliderFloat("V1 X", &vertices[7 * 1],  -1.0f, 1.0f);
        ImGui::SliderFloat("V1 Y", &vertices[7 * 1 + 1],  -1.0f, 1.0f);

        ImGui::SliderFloat("V2 X", &vertices[7 * 2],  -1.0f, 1.0f);
        ImGui::SliderFloat("V2 Y", &vertices[7 * 2 + 1],  -1.0f, 1.0f);

        ImGui::SliderFloat("V3 X", &vertices[7 * 3],  -1.0f, 1.0f);
        ImGui::SliderFloat("V3 Y", &vertices[7 * 3 + 1], -1.0f, 1.0f);

        ImGui::End();
    }

private:
    std::shared_ptr<Razor::VertexArray> m_VertexArray;
    std::shared_ptr<Razor::Shader> m_Shader;
    std::shared_ptr<Razor::OrthographicCamera> m_OrthoCamera;

    glm::vec3 m_CameraPosition = glm::vec3(0.0f);
    float m_CameraRotation = 0.0f;
    float m_CameraSpeed = 0.01f;
};

class Sandbox : public Razor::Application
{
public:
    Sandbox()
    {
        PushLayer(new TestLayer());
    }

    ~Sandbox()
    {

    }
};

Razor::Application* Razor::Application::CreateApplication()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    Razor::Log::Init();
    RZR_INFO("Engine starting...");

    auto app = Razor::Application::CreateApplication();
    app->Run();
    delete app;

    return 0;
}