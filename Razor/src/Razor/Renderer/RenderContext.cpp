#include "rzr_pch.h"
#include "RenderContext.h"

#include "Razor/Log.h"

#include "GLFW/glfw3.h"

#if (RENDERER_API == OPENGL_RENDERER_API)

#include "glad/glad.h"

#endif

namespace Razor
{
#if (RENDERER_API == OPENGL_RENDERER_API)

    RenderContext::RenderContext()
    {

    }

    void RenderContext::Init(void* NativeWindow)
    {
        glfwMakeContextCurrent((GLFWwindow*)NativeWindow);
        int LoadResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RZR_CORE_ASSERT(LoadResult, "Could not initialize Glad!");
    }

    void RenderContext::SwapBuffers(void* NativeWindow)
    {
        glfwSwapBuffers((GLFWwindow*)NativeWindow);
    }

#endif
}
