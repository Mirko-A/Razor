#pragma once

#include <string>
#include "glm/glm.hpp"

namespace Razor
{
    class Shader
    {
    public:
        Shader(const std::string& VertexSource, const std::string& FragmentSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniform(const std::string& Name, glm::mat4 Uniform);

    private:
        uint32_t m_ShaderID;
    };
}