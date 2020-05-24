//====================================================================================================
// Filename:	Merge.fx
// Created by:	Bhavil Gupta
// Description:	Simple shader for PostProcessing.
//====================================================================================================

Texture2D BaseTexture : register(t0);
Texture2D PPTexture: register(t1);
SamplerState textureSampler : register(s0);

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
	float4 cBase = BaseTexture.Sample(textureSampler, input.texCoord);
	float4 cTop = PPTexture.Sample(textureSampler, input.texCoord);
	
	float r = (cBase.r * (1.f - cTop.a)) + (cTop.r * (cTop.a));
	float g = (cBase.g * (1.f - cTop.a)) + (cTop.g * (cTop.a));
	float b = (cBase.b * (1.f - cTop.a)) + (cTop.b * (cTop.a));

	return float4(r, g, b, 1.f);
}
