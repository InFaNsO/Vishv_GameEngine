//====================================================================================================
// Filename:	Standard.fx
// Created by:	Bhavil Gupta
// Description: Default Shader for Vishv.
//====================================================================================================

cbuffer TransformBuffer			: register(b0)
{
	matrix world;
	matrix WVP;
	float4 viewPosition;
}

cbuffer LightBuffer				: register(b1)
{
	float3 LightDirection;
	float4 LightAmbient;
	float4 LightDiffuse;
	float4 LightSpecular;
}

cbuffer MaterialBuffer			: register(b2)
{
	float4 MaterialAmbient;
	float4 MaterialDiffuse;
	float4 MaterialSpecular;
	float4 MaterialPower;
}

cbuffer optionsBuffer : register(b3)
{
	float4 options;
}

Texture2D diffuseMap			: register(t0);
Texture2D specularMap			: register(t1);
Texture2D displacementMap		: register(t2);
Texture2D normalMap				: register(t3);
SamplerState textureSampler		: register(s0);

struct VSInput
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
	float3 dirToLight : TEXCOORD1;
	float3 dirToView : TEXCOORD2;
	float2 texCoord : TEXCOORD3;
};

VSOutput VS(VSInput input)
{
	VSOutput output = (VSOutput)0;
	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord,0).x;
    float4 pos = input.position + (float4(input.normal, 0.0f) * displacement * options.r);
	
	float3 normal = mul(input.normal, (float3x3) world);
	float3 tangent = mul(input.tangent, (float3x3) world);
	float3 binormal = cross(normal, tangent);
	
	output.position = mul(pos, WVP);
	output.normal = normal;
	output.binormal = binormal;
	output.tangent = tangent;
	output.dirToLight = -LightDirection;
	output.dirToView = normalize(viewPosition.xyz - mul(pos, world).xyz);
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VSOutput input) : SV_Target
{
	float3 n = normalize(input.normal);
	float3 b = normalize(input.binormal);
	float3 t = normalize(input.tangent);
    float3x3 tbnw = float3x3(t, b, n);
    float4 norColor = normalMap.Sample(textureSampler, input.texCoord);
    float3 sampledNormal = float3((2.0f * norColor.xy) - 1.0f, norColor.z);

    float3 normal =  normalize(mul(sampledNormal, tbnw));

	float3 dirToLight= normalize(input.dirToLight);
	float3 dirToView = normalize(input.dirToView);

	float4 ambient = LightAmbient * MaterialAmbient;
	float d = saturate(dot(dirToLight, normal));
	float4 diffuse = LightDiffuse * MaterialDiffuse * d;

	float3 r = reflect(LightDirection.xyz, normal);
	float s = saturate(dot(dirToView, r));
	float4 specular = pow(s, MaterialPower.x) * LightSpecular * MaterialSpecular;

	float4 diffCol = diffuseMap.Sample(textureSampler, input.texCoord);
	float4 specVal = specularMap.Sample(textureSampler, input.texCoord);

	return ((ambient + diffuse) * diffCol) + (specular * specVal.r);
}
