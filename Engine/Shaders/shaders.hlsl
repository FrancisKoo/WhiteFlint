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
	float4x4 inverseOfModel;
	float4x4 view;
	float4x4 projection;
};

struct VSInput
{
	float3 positionOS : POSITION;
	float3 normalOS : NORMAL;
	float2 texcoord0 : TEXCOORD0;
};

struct PSInput
{
	float4 positionCS : SV_Position;
    float3 normalWS : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

PSInput VSMain(VSInput input)
{
    PSInput result;

	float4x4 mvp = mul(projection, mul(view, model));
	result.positionCS = mul(mvp, float4(input.positionOS * 10.0f, 1.0f));
	
	// Normal multiply inverse transpose of model matrix.
	result.normalWS = mul(input.normalOS, (float3x3)inverseOfModel);
	result.uv = input.texcoord0;

    return result;
}

float4 PSMain(PSInput input, bool bFront : SV_IsFrontFace) : SV_Target
{
	float4 result = 1.0f;
	
	/*******************************Debug.*******************************/
	// World normal.
	result.xyz = input.normalWS;
	// Normal interpolate exaggerate error check.
	//result.xyz = abs(length(input.normalWS) - 1.0f) * 10.0f;
	
	return result;
}
