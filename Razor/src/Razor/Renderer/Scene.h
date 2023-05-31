#pragma once

#include "glm/glm.hpp"

namespace Razor
{
    class Scene
    {
    private:
        struct SceneData
        {
            glm::mat4 ProjectionViewMatrix;
        };

    public:
        inline static std::shared_ptr<SceneData> GetSceneData()
        {
            return s_SceneData;
        }

    private:
        static std::shared_ptr<SceneData> s_SceneData;
    };
}