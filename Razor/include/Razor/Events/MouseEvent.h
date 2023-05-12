#pragma once

#include "Event.h"

namespace Razor
{
    class MouseMovedEvent : public Event
    {
    private:
        float m_MouseX;
        float m_MouseY;

    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y)
        {}

        inline float GetX() const
        {
            return m_MouseX;
        }

        inline float GetY() const
        {
            return m_MouseX;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGOTY(EventCategoryInput | EventCategoryMouse)
    };

    class MouseScrolledEvent : public Event
    {
    private:
        float m_OffsetX;
        float m_OffsetY;

    public:
        MouseScrolledEvent(float OffsetX, float OffsetY)
            : m_OffsetX(OffsetX), m_OffsetY(OffsetY)
        {}

        inline float GetOffsetX() const
        {
            return m_OffsetX;
        }

        inline float GetOffsetY() const
        {
            return m_OffsetY;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGOTY(EventCategoryInput | EventCategoryMouse)
    };

    class MouseButtonEvent : public Event
    {
    protected:
        int m_Button;

        MouseButtonEvent(int Button)
            : m_Button(Button)
        {}

    public:
        inline int GetMouseButton() const
        {
            return m_Button;
        }

        EVENT_CLASS_CATEGOTY(EventCategoryInput | EventCategoryMouse)
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int Button)
            : MouseButtonEvent(Button)
        {}

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int Button)
            : MouseButtonEvent(Button)
        {}

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}