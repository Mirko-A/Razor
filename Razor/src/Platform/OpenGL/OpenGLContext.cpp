#include "rzr_pch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Razor/Log.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Razor
{
    OpenGLContext::OpenGLContext()
    {

    }

    void OpenGLContext::Init(void* NativeWindow)
    {
        glfwMakeContextCurrent((GLFWwindow*) NativeWindow);
        int LoadResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RZR_CORE_ASSERT(LoadResult, "Could not initialize Glad!");
    }

    void OpenGLContext::SwapBuffers(void* NativeWindow)
    {
        glfwSwapBuffers((GLFWwindow*) NativeWindow);
    }
}
