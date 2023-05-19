#pragma once

#include "Razor/Core.h"
#include "Layer.h"

#include <vector>

namespace Razor
{
    class LayerStack
    {
    private:
        std::vector<Layer*> m_Layers;
        uint16_t m_LayerInsertIndex;

    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* Layer);
        void PopLayer(Layer* Layer);
        void PushOverlay(Layer* Overlay);
        void PopOverlay(Layer* Overlay);

        std::vector<Layer*>::iterator begin()
        {
            return m_Layers.begin();
        }        
        std::vector<Layer*>::iterator end()
        {
            return m_Layers.end();
        }
    };
}
