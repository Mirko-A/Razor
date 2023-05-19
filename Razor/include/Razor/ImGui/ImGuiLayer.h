#pragma once

#include "Razor/Layer.h"

/* Mire, 5/19/2023
   Usage of this class should be as follows:
   1. Create an object of ImGuiLayer and push it to the Layer Stack 
   2. For each frame (on frame update) call the Begin() function to start ImGui rendering 
   3. Call the RenderImGui() function which contains all of the ImGui element rendering calls
   4. Call the End() function to render all the ImGui elements 
   
   Note: All of this is done inside the OnUpdate function */

/* Forward declaration needed */
struct ImGuiIO;

namespace Razor
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;

        void Begin();
        void End(ImGuiIO& IO);
        void RenderImGui(ImGuiIO& IO);
    private:
        float m_Time = 0.0f;
    };
}
