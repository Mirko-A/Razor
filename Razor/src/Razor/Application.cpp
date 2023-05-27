#include "rzr_pch.h"
#include "Application.h"

#include "Layer.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

#define VERTEX_COUNT (4)
#define INDEX_COUNT  (6)

float vertices[VERTEX_COUNT * 3 * 4] =
{
     -0.8f,  -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.2f,  -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      0.2f,   0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     -0.8f,   0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
};

float vertices1[VERTEX_COUNT * 3 * 4] =
{
      0.5f,   0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.9f,   0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      0.9f,   0.9f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      0.5f,   0.9f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
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

        m_Renderer = std::make_unique<Renderer>();
        m_Renderer->CreateVertexArray();
        m_Renderer->CreateVertexBuffer(vertices, sizeof(vertices));
        m_Renderer->CreateVertexBuffer(vertices1, sizeof(vertices1));
        m_Renderer->CreateIndexBuffer(indices, sizeof(indices));

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
            ImVec4 ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w);
            glClear(GL_COLOR_BUFFER_BIT);

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

            m_Shader->Bind();

            // m_Renderer->GetVertexArray()->GetVertexBuffers().begin()->get()->SetData(vertices, sizeof(vertices));
            // m_Renderer->GetVertexArray()->GetVertexBuffers().begin()->get()->Bind();

            const auto& VertexArrayRef = m_Renderer->GetVertexArray();
            VertexArrayRef->Bind();

            for (const auto& VBO : VertexArrayRef->GetVertexBuffers())
            {
                //VBO->SetData(vertices, sizeof(vertices));
                VBO->Bind();

                BufferLayout Layout =
                {
                    { ShaderDataType::Float3, "vs_Position"},
                    { ShaderDataType::Float4, "vs_Color"},
                };

                VBO->SetLayout(Layout);
                VertexArrayRef->GetIndexBuffer()->Bind();

                glDrawElements(GL_TRIANGLES, INDEX_COUNT, GL_UNSIGNED_INT, nullptr);
            }

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