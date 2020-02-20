//====================================================================================================
// Filename:	Texturing.fx
// Created by:	Peter Chan
// Description:	Simple shader for PostProcessing.
//====================================================================================================

Texture2D diffuseMap : register(t0);
Texture2D preprocessedMap : register(t1);
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

// for motion blur -> https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch27.html

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 c = diffuseMap.Sample(textureSampler, input.texCoord) + preprocessedMap.Sample(textureSampler, input.texCoord);
    //c /= 2.0f;
    return c;

    float xSub = 2.0f / 1280.0f;
    float ySub = 2.0f / 720.0f;

//    if (((input.texCoord.y + opptions.x) * 720.0f)  % 20.0f < 10.0f)
//    {
//        return diffuseMap.Sample(textureSampler, input.texCoord);
//    }
//	return float4(0.0f, diffuseMap.Sample(textureSampler, input.texCoord).g, 0.0f, 1.0f);
}
