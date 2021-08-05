#include "pch.h"
#include "Renderer.h"
#include "Core.h"
#include "Core.g.cpp"

namespace winrt::Engine::implementation
{
	void Core::CreateRenderer(Microsoft::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel)
	{
        auto panelNative{ swapChainPanel.as<ISwapChainPanelNative>() };
		m_renderer = std::make_unique<Renderer>(lround(swapChainPanel.ActualWidth()), lround(swapChainPanel.ActualHeight()), panelNative.get());
		m_renderer->Init();
		auto handler = [=](IInspectable const&, IInspectable const& args)
		{
			auto renderingEventArgs = args.as<Microsoft::UI::Xaml::Media::RenderingEventArgs>();
			static auto lastDuration = renderingEventArgs.RenderingTime();
			auto nowDuration = renderingEventArgs.RenderingTime();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(nowDuration - lastDuration);

			m_renderer->Tick();
			swapChainPanel.FindName(L"textBlock").as<Microsoft::UI::Xaml::Controls::TextBlock>().Text(L"MS:" + to_hstring(duration.count() / 1000.0));
			lastDuration = renderingEventArgs.RenderingTime();
		};
		m_renderingEvent = Microsoft::UI::Xaml::Media::CompositionTarget::Rendering(handler);
    }

	void Core::DestroyRenderer()
	{
		m_renderer->Destroy();
		Microsoft::UI::Xaml::Media::CompositionTarget::Rendering(m_renderingEvent);
		m_renderer.reset();
	}

	void Core::SetClearColor(Windows::UI::Color color)
	{
		const FLOAT clearColor[4] = { color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f };
		m_renderer->SetClearColor(clearColor);
	}

}
