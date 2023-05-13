#include "rzr_pch.h"
#include "Razor/Application.h"

#include "Razor/Layer.h"
#include "Razor/ImGui/ImGuiLayer.h"
#include "Razor/Input.h"

#include "GLFW/glfw3.h"

namespace Razor
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        RZR_CORE_ASSERT(s_Instance == nullptr, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_FN(Application::OnEvent));
    }

    Application::~Application() {}

    void Application::Run()
    {
        while (m_Running)
        {
            for (Layer* Layer : m_LayerStack)
            {
                Layer->OnUpdate();
            }

            auto [x, y] = Input::GetMousePos();

            RZR_CORE_INFO("MOUSE: {0}, {1}", x, y);

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

    // SANDBOX APPLICATION IS CREATED HERE
    class Sandbox : public Razor::Application
    {
    public:
        Sandbox()
        {
            PushLayer(new Razor::ImGuiLayer());
        }

        ~Sandbox()
        {

        }
    };

    Razor::Application* Razor::CreateApplication()
    {
        return new Sandbox;
    }
}