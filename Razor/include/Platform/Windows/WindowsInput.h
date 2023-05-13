#pragma once

#include "Razor/Input.h"

namespace Razor
{
    class WindowsInput : public Input
    {
    protected:
        bool IsKeyPressedImpl(int KeyCode) const override;
        bool IsMouseButtonPressedImpl(int Button) const override;
        std::pair<float, float> GetMousePosImpl() const override;
        float GetMouseXImpl() const override;
        float GetMouseYImpl() const override;
    };
}