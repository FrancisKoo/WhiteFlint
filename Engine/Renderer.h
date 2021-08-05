#pragma once

class Renderer
{
public:
	Renderer(UINT width, UINT height, ISwapChainPanelNative* swapChainPanelNative);
	~Renderer();

	void Init();
	void Tick();
	void Destroy();

	UINT GetWidth() const { return m_width; }
	UINT GetHeight() const { return m_height; }

	void SetClearColor(const FLOAT color[4])
	{
		ClearColor[0] = color[0];
		ClearColor[1] = color[1];
		ClearColor[2] = color[2];
		ClearColor[3] = color[3];
	};

private:
	void GetHardwareAdapter(_In_ IDXGIFactory1* pFactory, _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter);

	UINT m_width;
	UINT m_height;
	float m_aspectRatio;

	FLOAT ClearColor[4];

	winrt::com_ptr<ISwapChainPanelNative> m_swapChainPanelNative;

	static const UINT FrameCount = 2;
	UINT m_frameIndex;

	// Pipeline objects.
	winrt::com_ptr<ID3D12Device> m_device;
	winrt::com_ptr<ID3D12CommandQueue> m_commandQueue;
	winrt::com_ptr<IDXGISwapChain3> m_swapChain;
	winrt::com_ptr<ID3D12DescriptorHeap> m_rtvHeap;
	UINT m_rtvDescriptorSize;
	winrt::com_ptr<ID3D12Resource> m_renderTargets[FrameCount];
	winrt::com_ptr<ID3D12CommandAllocator> m_commandAllocator;
	winrt::com_ptr<ID3D12GraphicsCommandList> m_commandList;
	winrt::com_ptr<ID3D12Fence> m_fence;
	UINT64 m_fenceValue;
	HANDLE m_fenceEvent;
	winrt::com_ptr<ID3D12PipelineState> m_pipelineState;

	void LoadPipeline();
	void LoadAssets();
	void PopulateCommandList();
	void WaitForPreviousFrame();
};

