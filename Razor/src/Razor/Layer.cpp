#include "rzr_pch.h"
#include "Razor/Layer.h"

namespace Razor
{
    Layer::Layer(const std::string& Name)
        : m_DebugName(Name)
    {}

    Layer::~Layer() {}
}