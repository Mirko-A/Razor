#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Layer.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Razor/Renderer/Renderer.h"
#include "Razor/Renderer/Shader.h"

/* Mire, 5/20/2023
   Razor has been converted into a static library. This means that
   as of right now the usage of Razor by clients is as follows:
   1. Create a child of the Application class
   2. Implement the CreateApplication method
   3. Create an instance of the application in your main function and
   4. Run the application

   For more information, see an example main() function in Razor.h */

namespace Razor
{
    class Application
    {
    public:
        static Application* CreateApplication();

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
        static Application* s_Instance;
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        std::unique_ptr<Renderer> m_Renderer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

        unsigned int m_VertexArray;

        std::unique_ptr<Shader> m_Shader;

    private:
        bool OnWindowClose(WindowCloseEvent e);
    };
}