//====================================================================================================
// Filename:	DoLighting.fx
// Created by:	Bhavil Gupta
// Description: Shader that applies Light.
//====================================================================================================

cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix WVP;
	float4 viewPosition;
}

cbuffer LightBuffer : register(b1)
{
	float3 LightDirection;
	float4 LightAmbient;
	float4 LightDiffuse;
	float4 LightSpecular;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 MaterialAmbient;
	float4 MaterialDiffuse;
	float4 MaterialSpecular;
	float4 MaterialPower;
}

struct VSInput
{
	float4 position : POSITION;
	float3 normal : NORMAL;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VSOutput VS(VSInput input)
{
	VSOutput output = (VSOutput)0;
	output.position = mul(input.position, WVP);

	float4 ambient = LightAmbient * MaterialAmbient;
	float3 dirToLight = -LightDirection;
	float3 NormalWorld = mul(input.normal,(float3x3) world);
    float d = saturate(dot(dirToLight, NormalWorld));
	float4 diffuse = LightDiffuse * MaterialDiffuse * d;

    float3 dirToView = normalize(viewPosition.xyz - mul(input.position, world).xyz);
    float3 r = reflect(LightDirection.xyz, NormalWorld);
    float s = saturate(dot(dirToView, r));
    float4 specular = pow(s, MaterialPower.x) * LightSpecular * MaterialSpecular;

	output.color = ambient + diffuse + specular;
	return output;
}

float4 PS(VSOutput input) : SV_Target
{
	return input.color;
}
