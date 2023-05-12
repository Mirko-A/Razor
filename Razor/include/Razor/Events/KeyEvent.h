#pragma once

#include "Event.h"

namespace Razor
{
    class KeyEvent : public Event
    {
    protected:
        int m_KeyCode;

        KeyEvent(int KeyCode)
            : m_KeyCode(KeyCode)
        {}

    public:
        inline int GetKeyCode() const 
        { 
            return m_KeyCode; 
        }


        EVENT_CLASS_CATEGOTY(EventCategoryInput | EventCategoryKeyboard)
    };

    class KeyPressedEvent : public KeyEvent
    {
    private:
        int m_RepeatCount;

    public:
        KeyPressedEvent(int KeyCode, int RepeatCount)
            : KeyEvent(KeyCode), m_RepeatCount(RepeatCount)
        {}

        inline int GetRepeatCount() const
        {
            return m_RepeatCount;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int KeyCode)
            : KeyEvent(KeyCode)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}