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



cbuffer OptionsBuffer : register(b3)
{
    float4 opptions;
}

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

    float radius = opptions.w;
    radius = 5.0f;
    //float3x3 ker;
    //ker._11 = opptions.x;
    //ker._12 = opptions.y;
    //ker._13 = opptions.z;
    //ker._21 = opptions.y;
    //ker._31 = opptions.z;
    //ker._23 = opptions.y;
    //ker._33 = opptions.z;
    //ker._32 = opptions.y;
	//
    //ker._22 = ker._12 * ker._21;
	//
    //float kerSum = ker._11 + ker._12 + ker._13 + ker._21 + ker._22 + ker._23 + ker._31 + ker._32 + ker._33;

	float xSub = 1.0f / 1280.0f;
	float ySub = 1.0f / 720.0f;
    float2 uv = input.texCoord;

    float4 color;
    color.x = 0.0f;
    color.y = 0.0f;
    color.z = 0.0f;
    color.w = 1.0f;

    int count = 0;

	[unroll(10)]
    for (int i = (int)-radius; i < (int)radius; ++i)
    {
		[unroll(10)]
        for (int j = (int) -radius; j < (int) radius; ++j)
        {
            color += diffuseMap.Sample(textureSampler, float2(uv.x + ((float)i * xSub), uv.y + ((float)j * ySub)));
            count += 1;
        }
    }

    return color / count;


   //    float4 color =
	//(diffuseMap.Sample(textureSampler, float2(uv.x - xSub, uv.y - ySub)) * ker._11) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x + xSub, uv.y - ySub)) * ker._13) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x, uv.y - ySub)) * ker._12) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x - xSub, uv.y + ySub)) * ker._31) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x + xSub, uv.y + ySub)) * ker._33) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x, uv.y + ySub)) * ker._32) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x - xSub, uv.y)) * ker._21) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x + xSub, uv.y)) * ker._23) +
	//(diffuseMap.Sample(textureSampler, float2(uv.x, uv.y)) * ker._22);
   //
   //    color /= kerSum;
   //    return color;

   //}
//
//return diffuseMap.Sample(textureSampler, input.texCoord);
}
