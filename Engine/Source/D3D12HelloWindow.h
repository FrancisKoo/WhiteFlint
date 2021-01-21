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

using namespace SimpleMath;

class D3D12HelloWindow : public DXSample
{
public:
    D3D12HelloWindow(UINT width, UINT height, std::wstring name);

    void OnInit() override;
    void OnUpdate() override;
    void OnRender() override;
    void OnDestroy() override;

    //void OnKeyDown(UINT8 key) override;
    //void OnKeyUp(UINT key);

    class Transform
    {
    public:
        Transform() { Reset(); }

        void Translate(float x, float y, float z)
        {
            position.x += x;
            position.y += y;
            position.z += z;
        }

        void Rotate(float x, float y, float z)
        {
            rotation.x += x;
            rotation.y += y;
            rotation.z += z;
        }

        void Scale(float x, float y, float z)
        {
            scale.x += x;
            scale.y += y;
            scale.z += z;
        }

        Matrix GetModelMatrix()
        {
            Matrix t, r, s;
            t = Matrix::CreateTranslation(position);
            r = Matrix::CreateFromYawPitchRoll(rotation.x, rotation.y, rotation.z);
            s = Matrix::CreateScale(scale);
            return s * r * t;
        }

        void Reset()
        {
            position = rotation = Vector3::Zero;
            scale = Vector3::One;
        }

        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
    };

    // Object property.
    std::shared_ptr<Transform> m_transform;

private:
    // In this sample we overload the meaning of FrameCount to mean both the maximum
    // number of frames that will be queued to the GPU at a time, as well as the number
    // of back buffers in the DXGI swap chain. For the majority of applications, this
    // is convenient and works well. However, there will be certain cases where an
    // application may want to queue up more frames than there are back buffers
    // available.
    // It should be noted that excessive buffering of frames dependent on user input
    // may result in noticeable latency in your app.
    static const UINT FrameCount = 2;

    struct Vertex
    {
        Vector3 position;
        Vector4 color;
    };

    struct VSConstants
    {
        Matrix model;
        float padding[48];
    };


    // Pipeline objects.
    CD3DX12_VIEWPORT m_viewport;
    CD3DX12_RECT m_scissorRect;
    com_ptr<IDXGISwapChain3> m_swapChain;
    com_ptr<ID3D12Device> m_device;
    com_ptr<ID3D12Resource> m_renderTargets[FrameCount];
    com_ptr<ID3D12CommandAllocator> m_commandAllocators[FrameCount];
    com_ptr<ID3D12CommandQueue> m_commandQueue;
    com_ptr<ID3D12RootSignature> m_rootSignature;
    com_ptr<ID3D12DescriptorHeap> m_rtvHeap;
    com_ptr<ID3D12PipelineState> m_pipelineState;
    com_ptr<ID3D12GraphicsCommandList> m_commandList;
    UINT m_rtvDescriptorSize;

    // App resources.
    com_ptr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

    // Vertex shader constants.
    com_ptr<ID3D12Resource> m_vsConstantsBuffer;
    VSConstants m_vsConstantsData;
    com_ptr<ID3D12DescriptorHeap> m_cbvHeap;
    UINT8* m_pVSConstantsData;

    // Synchronization objects.
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    com_ptr<ID3D12Fence> m_fence;
    UINT64 m_fenceValues[FrameCount];

    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void MoveToNextFram();
    void WaitForGpu();
};
