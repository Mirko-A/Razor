#pragma once

namespace Razor
{
    class RenderContext
    {
    public:
        virtual ~RenderContext() {}

        virtual void Init(void* NativeWindow) = 0;
        virtual void SwapBuffers(void* NativeWindow) = 0;
    };
}