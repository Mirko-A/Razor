#pragma once

#include "Razor/Renderer/RenderContext.h"

namespace Razor
{
    class OpenGLContext : public RenderContext
    {
    public:
        OpenGLContext();

        void Init(void* NativeWindow) override;
        void SwapBuffers(void* NativeWindow) override;
    };
}