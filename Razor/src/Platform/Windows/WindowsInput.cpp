#include "rzr_pch.h"
#include "Platform/Windows/WindowsInput.h"

#include "Razor/Application.h"

#include "GLFW/glfw3.h"

namespace Razor
{
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int KeyCode) const
    {
        int State = glfwGetKey((GLFWwindow*) Application::Get()
                                                         .GetWindow()
                                                         .GetNativeWindow(), KeyCode);

        return State == GLFW_PRESS || State == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int Button) const
    {
        int State = glfwGetMouseButton((GLFWwindow*)Application::Get()
                                                                .GetWindow()
                                                                .GetNativeWindow(), Button);
        return State == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl() const
    {
        double x, y;
        glfwGetCursorPos((GLFWwindow*)Application::Get()
                                                  .GetWindow()
                                                  .GetNativeWindow(), &x, &y);

        return std::pair<float, float>((float) x, (float) y);
    }

    float WindowsInput::GetMouseXImpl() const
    {
        auto [x, y] = GetMousePosImpl();

        return x;
    }

    float WindowsInput::GetMouseYImpl() const
    {
        auto [x, y] = GetMousePosImpl();

        return y;
    }
}