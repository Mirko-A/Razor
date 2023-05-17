#include "rzr_pch.h"
#include "Razor/ImGui/ImGuiLayer.h"

#include "Razor/Application.h"

#include "Razor/Input.h"
#include "Razor/Log.h"

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "glad/glad.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "GLFW/glfw3.h"

#define GLSL_VERSION "#version 410"

namespace Razor
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {}

    ImGuiLayer::~ImGuiLayer()
    {}

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) Application::Get()
                                                               .GetWindow()
                                                               .GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init(GLSL_VERSION);
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
        ImVec4 ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        int DisplayWidth;
        int DisplayHeight;

        ImGuiIO& IO = ImGui::GetIO();
        Application& App = Application::Get();

        IO.DisplaySize = ImVec2((float) App.GetWindow().GetWidth(), (float) App.GetWindow().GetHeight());

        float Time = (float)glfwGetTime();
        float dt = m_Time - Time;
        IO.DeltaTime = (dt > 0) ? dt : (1.0f / 60.0f);
        m_Time = Time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // 1. Show a demo window 
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / IO.Framerate, IO.Framerate);
            ImGui::End();

            ImGui::Render();
        }

        glfwGetFramebufferSize((GLFWwindow*) Application::Get().GetWindow().GetNativeWindow(), &DisplayWidth, &DisplayHeight);
        glViewport(0, 0, DisplayWidth, DisplayHeight);

        glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnEvent(Event& e)
    {

    }
}
