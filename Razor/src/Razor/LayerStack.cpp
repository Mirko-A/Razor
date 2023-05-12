#include "rzr_pch.h"
#include "Razor/LayerStack.h"

namespace Razor
{
    LayerStack::LayerStack()
    {
        m_LayerInsert = m_Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (Layer* Layer : m_Layers)
        {
            delete Layer;
        }
    }

    void LayerStack::PushLayer(Layer* Layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, Layer);
    }

    void LayerStack::PopLayer(Layer* Layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), Layer);
        if (it != m_Layers.end())
        {
            m_LayerInsert--;
            m_Layers.erase(it);
        }
    }

    void LayerStack::PushOverlay(Layer* Overlay)
    {
        m_Layers.emplace_back(Overlay);
    }

    void LayerStack::PopOverlay(Layer* Overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), Overlay);
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
        }
    }
}