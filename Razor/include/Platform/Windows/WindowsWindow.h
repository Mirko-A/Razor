#pragma once

#include "Razor/Window.h"
#include "glad/glad.h"

namespace Razor
{
    class WindowsWindow : public Window
    {
    private:
        GLFWwindow* m_NativeWindow;

        struct WindowData
        {
            std::string Title;
            uint16_t Width;
            uint16_t Height;

            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;

    public:
        WindowsWindow(const WindowProps& Props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline void* GetNativeWindow() const override
        {
            return (void*) m_NativeWindow;
        }

        inline uint16_t GetWidth() const override
        {
            return m_Data.Width;
        }
        
        inline uint16_t GetHeight() const override
        {
            return m_Data.Height;
        }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& Callback) override
        {
            m_Data.EventCallback = Callback;
        }
        void SetVSync(bool Enabled) override;
        bool IsVSync() const override;
    private:
        virtual void Init(const WindowProps& Props);
        virtual void Shutdown();
    };

}