#pragma once

namespace Razor
{
    class Input
    {
    public:
        inline static bool IsKeyPressed(int KeyCode)
        { 
            return s_Instance->IsKeyPressedImpl(KeyCode);
        }

        inline static bool IsMouseButtonPressed(int Button)
        {
            return s_Instance->IsMouseButtonPressedImpl(Button);
        }

        inline static std::pair<float, float> GetMousePos()
        {
            return s_Instance->GetMousePosImpl();
        }

        inline static float GetMouseX()
        {
            return s_Instance->GetMouseXImpl();
        }

        inline static float GetMouseY()
        {
            return s_Instance->GetMouseYImpl();
        }

    protected:
        virtual bool IsKeyPressedImpl(int KeyCode) const = 0;
        virtual bool IsMouseButtonPressedImpl(int Button) const = 0;
        virtual std::pair<float, float> GetMousePosImpl() const = 0;
        virtual float GetMouseXImpl() const = 0;
        virtual float GetMouseYImpl() const = 0;

    protected:
        static Input* s_Instance;
    };
}