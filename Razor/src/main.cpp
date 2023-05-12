#include "rzr_pch.h"
#include "Razor.h"

class Sandbox : public Razor::Application
{
public:
    Sandbox()
    {
        PushLayer(new Razor::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
};

Razor::Application* Razor::CreateApplication()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    Razor::Log::Init();
    RZR_INFO("Engine starting...");

    auto app = Razor::CreateApplication();
    app->Run();
    delete app;

    return 0;
}