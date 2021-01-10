//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include "DXSample.h"

using namespace DirectX;

// Note that while ComPtr is used to manage the lifetime of resources on the CPU,
// it has no understanding of the lifetime of resources on the GPU. Apps must account
// for the GPU lifetime of resources to avoid destroying objects that may still be
// referenced by the GPU.
// An example of this can be found in the class method: OnDestroy().
using winrt::com_ptr;

class D3D12HelloWindow : public DXSample
{
public:
    D3D12HelloWindow(UINT width, UINT height, std::wstring name);

    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;
    void OnDestroy() override;

private:
    static const UINT FrameCount = 2;

    struct Vertex
    {
        XMFLOAT3 position;
        XMFLOAT4 color;
    };

    struct SceneConstantBuffer
    {
        XMFLOAT4 offset;
        float padding[60]; // Padding so the constant buffer is 256-byte aligned.
    };
    static_assert((sizeof(SceneConstantBuffer) % 256) == 0, "Constant Buffer size must be 256-byte aligned");

    // Pipeline objects.
    CD3DX12_VIEWPORT m_viewport;
    CD3DX12_RECT m_scissorRect;
    com_ptr<IDXGISwapChain3> m_swapChain;
    com_ptr<ID3D12Device> m_device;
    com_ptr<ID3D12Resource> m_renderTargets[FrameCount];
    com_ptr<ID3D12CommandAllocator> m_commandAllocator;
    com_ptr<ID3D12CommandQueue> m_commandQueue;
    com_ptr<ID3D12RootSignature> m_rootSignature;
    com_ptr<ID3D12DescriptorHeap> m_rtvHeap;
    com_ptr<ID3D12DescriptorHeap> m_cbvHeap;
    com_ptr<ID3D12PipelineState> m_pipelineState;
    com_ptr<ID3D12GraphicsCommandList> m_commandList;
    UINT m_rtvDescriptorSize;

    // App resources.
    com_ptr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
    com_ptr<ID3D12Resource> m_constantBuffer;
    SceneConstantBuffer m_constantBufferData;    
    UINT8* m_pCbvDataBegin;

    // Synchronization objects.
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    com_ptr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;

    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void WaitForPreviousFrame();
};