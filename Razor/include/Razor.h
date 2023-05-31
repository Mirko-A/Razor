#pragma once

/* File is for use by Razor application  */

/* 

********* EXAMPLE MAIN FUNCTON **********

int main(int argc, char** argv)
{
    Razor::Log::Init();
    RZR_INFO("Engine starting...");

    auto app = Razor::Application::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

*/

#include "Razor/Utility/KeyCodes.h"

#include "Razor/Application.h"
#include "Razor/Log.h"

#include "Razor/Layer.h"
#include "Razor/ImGui/ImGuiLayer.h"
#include "Razor/Input.h"

#include "Razor/Renderer/Renderer.h"
#include "Razor/Renderer/RenderCommand.h"
#include "Razor/Renderer/VertexArray.h"
#include "Razor/Renderer/Shader.h"
#include "Razor/Renderer/Camera.h"