#include "Razor.h"

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
        ImGui::Begin("Test layer window");
        static ImVec4 ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        static float f = 0.0f;
        static int counter = 0;

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&ClearColor); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
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