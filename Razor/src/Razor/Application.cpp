#include "rzr_pch.h"
#include "Application.h"

#include "Layer.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

// TODO: Remove once VBO and IBO abstraction is in place
#include "glad/glad.h"

#define VERTEX_COUNT (8)
#define INDEX_COUNT  (6 * 3)

float vertices[VERTEX_COUNT * 3] =
{
     -0.145f,  0.185f, 0.0f,
     -0.259f,  0.309f, 0.0f,
     -0.434f,  0.227f, 0.0f,
     -0.454f,  0.010f, 0.0f,
     -0.145f, -0.381f, 0.0f,
      0.165f,  0.010f, 0.0f,
     -0.031f,  0.310f, 0.0f,
};

uint32_t indices[INDEX_COUNT] =
{
    3, 1, 2,
    3, 0, 1,
    4, 0, 3,
    4, 5, 0,
    0, 5, 7,
    5, 6, 7,
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
        m_VertexBuffer = m_Renderer->CreateVertexBuffer(vertices, sizeof(vertices));
        m_IndexBuffer =  m_Renderer->CreateIndexBuffer(indices, sizeof(indices));

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

            glGenVertexArrays(1, &m_VertexArray);
            glBindVertexArray(m_VertexArray);

            m_VertexBuffer->SetData(vertices, sizeof(vertices));
            m_VertexBuffer->Bind();

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

            m_IndexBuffer->Bind();

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, INDEX_COUNT, GL_UNSIGNED_INT, nullptr);

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