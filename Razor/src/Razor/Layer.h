#pragma once

#include "Razor/Core.h"
#include "Razor/Events/Event.h"

#include "imgui.h"

namespace Razor
{
    class Layer
    {
    public:
        Layer(const std::string& Name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& e) {}

        virtual void RenderImGui() {}

        inline const std::string& GetName() const
        {
            return m_DebugName;
        }
    protected:
        std::string m_DebugName;
    };
}