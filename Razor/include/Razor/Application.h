#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Layer.h"
#include "LayerStack.h"

namespace Razor
{
    class Application
    {
    private:
        static Application* s_Instance;
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        void PushLayer(Layer* Layer);
        void PushOverlay(Layer* Overlay);

        inline static Application& Get()
        {
            return *s_Instance;
        }

        inline Window& GetWindow() const
        {
            return *m_Window;
        }

    private:
        bool OnWindowClose(WindowCloseEvent e);
    };

    // Mire, 5/13/2023
    // As of right now, a sandbox class exists inside Application.cpp 
    // file which used to create an instance of 'Application'
    // TODO: Create a child class of 'Application' and implement
    // a version of this function based on the current needs of the Engine
    Application* CreateApplication();
}