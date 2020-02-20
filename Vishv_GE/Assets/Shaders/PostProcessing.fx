//====================================================================================================
// Filename:	Texturing.fx
// Created by:	Peter Chan
// Description:	Simple shader for PostProcessing.
//====================================================================================================

Texture2D diffuseMap : register(t0);
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

//cbuffer OptionsBuffer : register(b0)
//{
//    float4 opptions;
//}

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
	//if (opptions.x > 0.0f)			//options 1 will give pixeleated
	//{
	//	float2 uv = input.texCoord;
	//	uv.x = (int) (uv.x * 240) / 240.0f;
	//	uv.y = (int) (uv.y * 135) / 135.0f;
	//	return diffuseMap.Sample(textureSampler, uv);
	//}
	//if (opptions.y > 0.0f)		//options 2 will blur the objects
	//{
        //float2 uv = input.texCoord;
        //float4 color = diffuseMap.Sample(textureSampler, (uv.x - 1, uv.y - 1)) + diffuseMap.Sample(textureSampler, (uv.x, uv.y - 1)) + diffuseMap.Sample(textureSampler, (uv.x + 1, uv.y - 1)) +
		//				diffuseMap.Sample(textureSampler, (uv.x - 1, uv.y)) + diffuseMap.Sample(textureSampler, (uv.x, uv.y)) + diffuseMap.Sample(textureSampler, (uv.x + 1, uv.y)) +
		//				diffuseMap.Sample(textureSampler, (uv.x - 1, uv.y + 1)) + diffuseMap.Sample(textureSampler, (uv.x, uv.y + 1)) + diffuseMap.Sample(textureSampler, (uv.x + 1, uv.y + 1));
		//
        //color.r = color.r / 9;
        //color.g = color.g / 9;
        //color.b = color.b / 9;
        //color.a = color.a / 9;
    return diffuseMap.Sample(textureSampler,input.texCoord);
    //}
	//
	//return diffuseMap.Sample(textureSampler, input.texCoord);
}
