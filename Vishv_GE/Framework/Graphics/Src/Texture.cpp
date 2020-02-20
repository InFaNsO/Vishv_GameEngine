#include "Precompiled.h"
#include "Texture.h"
#include "D3DUtil.h"

#include <DirectXTK/Inc/WICTextureLoader.h>

using namespace Vishv;
using namespace Vishv::Graphics;

void Texture::Initialize(const std::filesystem::path& fileName)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(GetDevice(), GetContext(), fileName.c_str(), nullptr, &mShaderResourceView);
	VISHVASSERT(SUCCEEDED(hr), "[Vishv::Graphics::texture::Initialize] failed to load texture %s.", fileName.string().c_str());
}

void Texture::Terminate()
{
	SafeRelease(mShaderResourceView);
}

void Texture::BindPS(uint32_t slot) const
{
	GetContext()->PSSetShaderResources(slot, 1, &mShaderResourceView);
}

void Texture::BindVS(uint32_t slot) const
{
	GetContext()->VSSetShaderResources(slot, 1, &mShaderResourceView);
}


Texture::~Texture()
{
	VISHVASSERT(mShaderResourceView == nullptr, "[Vishv::Graphics::Texture] Terminate not called on Texture.");
}