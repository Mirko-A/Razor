#pragma once

#include "Event.h"

namespace Razor
{
    class WindowResizeEvent : public Event
    {
    private:
        uint16_t m_Width;
        uint16_t m_Height;

    public:
        WindowResizeEvent(uint16_t Width, uint16_t Height)
            : m_Width(Width), m_Height(Height)
        {

        }

        inline uint16_t GetWidth() const
        {
            return m_Width;
        }
        
        inline uint16_t GetHeight() const
        {
            return m_Height;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGOTY(EventCategoryApplication)
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGOTY(EventCategoryApplication)
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGOTY(EventCategoryApplication)
    };

    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGOTY(EventCategoryApplication)
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGOTY(EventCategoryApplication)
    };
}