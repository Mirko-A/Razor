#pragma once

#include <string>

namespace Razor
{
    class Shader
    {
    public:
        Shader(const std::string& VertexSource, const std::string& FragmentSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_RendererID;
    };
}