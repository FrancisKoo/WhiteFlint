#pragma once
#include "Core.g.h"

namespace winrt::Engine::implementation
{
	struct Core : CoreT<Core>
    {
        Core() = default;

        void CreateRenderer(Microsoft::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel);
        void DestroyRenderer();
        void SetClearColor(Windows::UI::Color color);
    private:
        event_token m_renderingEvent;
        std::unique_ptr<Renderer> m_renderer;
    };
}
namespace winrt::Engine::factory_implementation
{
    struct Core : CoreT<Core, implementation::Core>
    {
    };
}
