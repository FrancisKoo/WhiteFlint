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
	float4 padding[8];
};

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
{
    PSInput result;
    

	float4x4 mvp = mul(view, model);
	result.position = mul(mvp, position);
	result.color = color;

    return result;
}

float4 PSMain(PSInput input, bool bFront : SV_IsFrontFace) : SV_TARGET
{
	float4 result = bFront ? input.color : float4(0, 0, 0, 1);
	return result;
}
