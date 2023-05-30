#pragma once

namespace Razor
{
    class RenderContext
    {
    public:
        RenderContext();

        void Init(void* NativeWindow);
        void SwapBuffers(void* NativeWindow);
    };
}