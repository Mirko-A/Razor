#include "rzr_pch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Razor/Events/ApplicationEvent.h"
#include "Razor/Events/KeyEvent.h"
#include "Razor/Events/MouseEvent.h"

#include "imgui.h"

namespace Razor
{
    static bool s_GLFWInitialized = false;

    void WindowsWindow::Init(const WindowProps& Props)
    {
        m_Data.Title = Props.Title;
        m_Data.Width = Props.Width;
        m_Data.Height = Props.Height;

        RZR_CORE_INFO("Creating window {0} ({1}, {2})", Props.Title, Props.Width, Props.Height);

        if (s_GLFWInitialized == false)
        {
            // TODO: glfwTerminate on system shutdown
            int InitResult = glfwInit();
            RZR_CORE_ASSERT(InitResult, "Could not initialize GLFW!");
            glfwSetErrorCallback([](int error, const char* description)
                {
                    RZR_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
                });

            s_GLFWInitialized = true;
        }

        m_NativeWindow = glfwCreateWindow((int)Props.Width, (int)Props.Height, Props.Title.c_str(), nullptr, nullptr);
        m_Context = new OpenGLContext();
        m_Context->Init(m_NativeWindow);

        glfwSetWindowUserPointer(m_NativeWindow, &m_Data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_NativeWindow, 
            [](GLFWwindow* window, int width, int height)
            {
                WindowData& Data = *((WindowData*) glfwGetWindowUserPointer(window));

                Data.Width  = width;
                Data.Height = height;

                WindowResizeEvent Event((uint16_t) width, (uint16_t) height);
                Data.EventCallback(Event);
            });

        glfwSetWindowCloseCallback(m_NativeWindow, 
            [](GLFWwindow* Window)
            {
                WindowData& Data = *((WindowData*)glfwGetWindowUserPointer(Window));

                WindowCloseEvent Event;
                Data.EventCallback(Event);
            });

        glfwSetKeyCallback(m_NativeWindow, 
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& Data = *((WindowData*)glfwGetWindowUserPointer(window));

                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent Event(key, 0);
                        Data.EventCallback(Event);
                    }
                    break;
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent Event(key);
                        Data.EventCallback(Event);
                    }
                    break;
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent Event(key, 1);
                        Data.EventCallback(Event);
                    }
                    break;
                    default:
                    {
                        RZR_CORE_WARN("{0} key event type is not supported!", action);
                    }
                    break;
                }
            });
        
        glfwSetMouseButtonCallback(m_NativeWindow, 
            [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& Data = *((WindowData*)glfwGetWindowUserPointer(window));

                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent Event(button);
                        Data.EventCallback(Event);
                    }
                    break;
                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent Event(button);
                        Data.EventCallback(Event);
                    }
                    break;
                    default:
                    {
                        RZR_CORE_WARN("{0} mouse event type is not supported!", action);
                    }
                    break;
                }
            });

        glfwSetScrollCallback(m_NativeWindow, 
            [](GLFWwindow* window, double xoffset, double yoffset)
            {
                WindowData& Data = *((WindowData*)glfwGetWindowUserPointer(window));

                MouseScrolledEvent Event((float) xoffset, (float) yoffset);
                Data.EventCallback(Event);
            });

        glfwSetCursorPosCallback(m_NativeWindow, 
            [](GLFWwindow* window, double xpos, double ypos)
            {
                WindowData& Data = *((WindowData*)glfwGetWindowUserPointer(window));

                MouseMovedEvent Event((float)xpos, (float)ypos);
                Data.EventCallback(Event);
            });
    }

    WindowsWindow::WindowsWindow(const WindowProps& Props)
    {
        Init(Props);
    }

    // Use this to create the window
    Window* Window::Create(const WindowProps& Props)
    {
        return new WindowsWindow(Props);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_NativeWindow);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers(m_NativeWindow);
    }

    void WindowsWindow::SetVSync(bool Enabled)
    {
        if (Enabled == true)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(1);
        }

        m_Data.VSync = true;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}