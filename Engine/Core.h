#pragma once
#include "Core.g.h"

namespace winrt::Engine::implementation
{
    struct Core : CoreT<Core>
    {
        Core() = default;

        hstring GetEngineName();
    };
}
namespace winrt::Engine::factory_implementation
{
    struct Core : CoreT<Core, implementation::Core>
    {
    };
}
