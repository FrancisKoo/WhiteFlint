#include "pch.h"
#include "Core.h"
#include "Core.g.cpp"

namespace winrt::Engine::implementation
{
    hstring Core::GetEngineName()
    {
        return L"White Flint";
    }

	float Core::GetEngineVersion()
	{
        return 0.01f;
	}

}
