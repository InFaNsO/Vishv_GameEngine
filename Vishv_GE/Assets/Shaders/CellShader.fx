//====================================================================================================
// Filename:	CellShader.fx
// Created by:	Bhavil Gupta
// Description:	Simple Cell Shader.
//====================================================================================================

Texture2D PreProcessorMap : register(t0);
SamplerState textureSampler : register(s0);

//buffers need to match the order in the Constant buffer bind functions

cbuffer OptionsBuffer : register(b0)
{
	float4 options;
	/*
		x = 1 / screen width
		y = 1 / screen height
		z = threshhold
		w = is not used
	*/
}

struct VS_INPUT
{
	float4 position	: POSITION;
	float2 texCoord	: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float2 texCoord	: TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;
	output.position = input.position;
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 c = PreProcessorMap.Sample(textureSampler, input.texCoord);
	
	//Sample all 3 colors around it
	
	float e11 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(-options.x, -options.y));
	float e12 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(0, -options.y));
	float e13 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(+options.x, -options.y));

	float e21 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(-options.x, 0));
	float e22 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(0, 0));
	float e23 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(+options.x, 0));

	float e31 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(-options.x, +options.y));
	float e32 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(0, +options.y));
	float e33 = PreProcessorMap.Sample(textureSampler, input.texCoord + float2(+options.x, +options.y));

	float t1 = e13 + e33 + (2 * e23) - e11 - (2 * e21) - e31;
	float t2 = e31 + (2 * e32) + e33 - e11 - (2 * e12) - e13;
	
	if ((t1 * t1 + t2 * t2) > options.z)
	{
		return float4(0.f, 0.f, 0.f, 1.0f);
	}
	return c;
}

