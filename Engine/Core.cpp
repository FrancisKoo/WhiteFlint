#include "pch.h"
#include "Core.h"
#include "Core.g.cpp"

namespace winrt::Engine::implementation
{
    hstring Core::GetEngineName()
    {
        return L"White Flint";
    }
}
