#include "rzr_pch.h"

#include "Scene.h"

namespace Razor
{
    std::shared_ptr<Scene::SceneData> Scene::s_SceneData = std::make_shared<Scene::SceneData>();
}