#include "rzr_pch.h"
#include "Application.h"

#include "Layer.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

#define VERTEX_COUNT (4)
#define INDEX_COUNT  (6)

float vertices[VERTEX_COUNT * (3 + 4)] =
{
     -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.2f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      0.2f,  0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     -0.8f,  0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
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

namespace Razor
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        RZR_CORE_ASSERT(s_Instance == nullptr, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

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

        m_VertexArray = RenderCommand::CreateVertexArray();
        m_VertexArray->AddVertexBuffer(RenderCommand::CreateVertexBuffer(vertices, sizeof(vertices), Layout));
        m_VertexArray->SetIndexBuffer(RenderCommand::CreateIndexBuffer(indices, sizeof(indices)));

        m_Shader = std::make_unique<Shader>(VertexSourceStringStream.str(), FragmentSourceStringStream.str());
    }

    Application::~Application() 
    {
        RZR_CORE_INFO("Application closing...");
    }

    void Application::Run()
    {
        while (m_Running)
        { 
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_Shader->Bind();

            for (const auto& VBO : m_VertexArray->GetVertexBuffers())
            {
                VBO->SetData(vertices, sizeof(vertices));

                Renderer::Submit(m_VertexArray);
            }

            Renderer::EndScene();

            for (Layer* Layer : m_LayerStack)
            {
                Layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* Layer : m_LayerStack)
            {
                Layer->RenderImGui();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent e)
    {
        m_Running = false;
        return true;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher Dispatcher(e);
        Dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.IsHandled() == true)
                break;
        }
    }

    void Application::PushLayer(Layer* Layer)
    {
        m_LayerStack.PushLayer(Layer);
        Layer->OnAttach();
    }

    void Application::PushOverlay(Layer* Overlay)
    {
        m_LayerStack.PushLayer(Overlay);
        Overlay->OnAttach();
    }
}