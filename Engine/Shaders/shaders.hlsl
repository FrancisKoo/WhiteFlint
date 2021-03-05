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

cbuffer VSConstants : register(b0)
{
	float4x4 model;
	float4x4 view;
	float4x4 projection;
	float4 padding[4];
};

struct VSInput
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct PSInput
{
	float4 position : SV_Position;
    float3 normal : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

PSInput VSMain(VSInput input)
{
    PSInput result;

	float4x4 mvp = mul(projection, mul(view, model));
	result.position = mul(mvp, input.position);
	result.normal = input.normal;
	result.uv = input.texcoord;

    return result;
}

float4 PSMain(PSInput input, bool bFront : SV_IsFrontFace) : SV_TARGET
{
	float4 result = 1;
	result.rg = bFront ? input.uv.xy : 0;
	
	return result;
}
