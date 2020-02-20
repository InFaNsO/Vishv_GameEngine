#include "Precompiled.h"
#include "D3DUtil.h"

#include "Texture.h"
#include "GraphicsSystem.h"

ID3D11ShaderResourceView* Vishv::Graphics::GetShaderResourceView(const Texture & texture)
{
	return texture.mShaderResourceView;
}

ID3D11Device * Vishv::Graphics::GetDevice()
{
	return GraphicsSystem::Get()->mD3DDdevice;
}

ID3D11DeviceContext * Vishv::Graphics::GetContext()
{
	return GraphicsSystem::Get()->mImmediateContext;
}