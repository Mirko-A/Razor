#pragma once

#include "Razor/Core.h"

namespace Razor
{
    // Mire, 5/6/2023 
    // Events in this engine are currently blocking, meaning when an event occurs it
    // immediately gets dispatched and must be dealt with right then and there.
    // For future, a better strategy might be to buffer events in an event
    // bus and process them during the "event" part of the update stage.

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

#define EVENT_CLASS_TYPE(type)  static  EventType GetStaticType() { return  EventType::##type; }            \
                                virtual EventType GetEventType() const override { return GetStaticType(); } \
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGOTY(category)  virtual int GetCategoryFlags() const override     \
                                        {                                                 \
                                            return (category);                            \
                                        }

    class Event
    {
        friend class EventDispatcher;
    protected:
        bool m_Handled = false;

    public:
        inline bool IsHandled() const
        {
            return m_Handled;
        }
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const    = 0;
        virtual int GetCategoryFlags() const   = 0;
        virtual std::string ToString() const 
        { 
            return GetName(); 
        }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    private:
        Event& m_Event;

    public:
        EventDispatcher(Event& e)
            : m_Event(e)
        {}

        template<typename T>
        bool Dispatch(EventFn<T> Callback)
        {
            bool Dispatched = false;

            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled = Callback(*(T*)&m_Event);
                Dispatched = true;
            }

            return Dispatched;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}