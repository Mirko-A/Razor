#pragma once

#include "rzr_pch.h"

#include "Core.h"
#include "Log.h"
#include "Events/Event.h"

#include "GLFW/glfw3.h"

namespace Razor
{
    struct WindowProps
    {
        std::string Title;
        uint16_t Width;
        uint16_t Height;

        WindowProps(const std::string& NewTitle = "Engine",
            uint16_t Width = 1280,
            uint16_t Height = 720)
            : Title(NewTitle), Width(Width), Height(Height)
        {}
    };

    // Interface representing a desktop system based Window
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual inline void* GetNativeWindow() const = 0;

        virtual uint16_t GetWidth() const = 0;
        virtual uint16_t GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;
        virtual void SetVSync(bool Enabled) = 0;
        virtual bool IsVSync() const = 0;

        static Window* Create(const WindowProps& Props = WindowProps());
    };
}