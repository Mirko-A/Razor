#include "Razor.h"

extern float vertices[];

// SANDBOX APPLICATION IS CREATED HERE
class TestLayer : public Razor::Layer
{
public:
    TestLayer(const std::string& Name = "Test layer")
    {

    }

    void OnEvent(Razor::Event& e)
    {
        if (e.GetEventType() == Razor::EventType::KeyPressed)
        {
            Razor::KeyPressedEvent& Event = (Razor::KeyPressedEvent&)e;
            RZR_INFO("KEY {0} PRESSED", (char)Event.GetKeyCode());
        }
    }

    void RenderImGui()
    {
        ImGui::Begin("Cube editor");
        ImGui::SliderFloat("V0 X", &vertices[7 * 0], -1.0f, 1.0f);
        ImGui::SliderFloat("V0 Y", &vertices[7 * 0 + 1],  -1.0f, 1.0f);

        ImGui::SliderFloat("V1 X", &vertices[7 * 1],  -1.0f, 1.0f);
        ImGui::SliderFloat("V1 Y", &vertices[7 * 1 + 1],  -1.0f, 1.0f);

        ImGui::SliderFloat("V2 X", &vertices[7 * 2],  -1.0f, 1.0f);
        ImGui::SliderFloat("V2 Y", &vertices[7 * 2 + 1],  -1.0f, 1.0f);

        ImGui::SliderFloat("V3 X", &vertices[7 * 3],  -1.0f, 1.0f);
        ImGui::SliderFloat("V3 Y", &vertices[7 * 3 + 1], -1.0f, 1.0f);

        ImGui::End();
    }
};

class Sandbox : public Razor::Application
{
public:
    Sandbox()
    {
        PushLayer(new TestLayer());
    }

    ~Sandbox()
    {

    }
};

Razor::Application* Razor::Application::CreateApplication()
{
    return new Sandbox;
}

int main(int argc, char** argv)
{
    Razor::Log::Init();
    RZR_INFO("Engine starting...");

    auto app = Razor::Application::CreateApplication();
    app->Run();
    delete app;

    return 0;
}