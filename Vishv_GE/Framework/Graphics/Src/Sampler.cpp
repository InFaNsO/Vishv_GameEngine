#include "Precompiled.h"
#include "Sampler.h"
#include "D3DUtil.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	D3D11_FILTER GetFilter(Sampler::Filter filter)
	{
		switch (filter)
		{
		case Sampler::Filter::Anistropic:
			return D3D11_FILTER_ANISOTROPIC;
		case Sampler::Filter::Linear:
			return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		case Sampler::Filter::Point:
			return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
		}
		return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	}

	D3D11_TEXTURE_ADDRESS_MODE GetAddressMode(Sampler::AddressMode mode)
	{
		switch (mode)
		{
		case Vishv::Graphics::Sampler::AddressMode::Border:
			return D3D11_TEXTURE_ADDRESS_BORDER;
			break;
		case Vishv::Graphics::Sampler::AddressMode::Clamp:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
			break;
		case Vishv::Graphics::Sampler::AddressMode::Mirror:
			return D3D11_TEXTURE_ADDRESS_MIRROR;
			break;
		case Vishv::Graphics::Sampler::AddressMode::Wrap:
			return D3D11_TEXTURE_ADDRESS_WRAP;
			break;
		default:
			return D3D11_TEXTURE_ADDRESS_BORDER;
			break;
		}
	}
}


Sampler::~Sampler()
{
	VISHVASSERT(mSampler == nullptr, "[Vishv::Graphics::Sampler] terminate not called");
}

void Sampler::Initialize(Sampler::Filter filter, Sampler::AddressMode addressMode)
{
	D3D11_FILTER d3dFilter = GetFilter(filter);
	D3D11_TEXTURE_ADDRESS_MODE d3dAddressMode = GetAddressMode(addressMode);

	D3D11_SAMPLER_DESC sampleDesc{};
	sampleDesc.Filter = d3dFilter;
	sampleDesc.AddressU = d3dAddressMode;
	sampleDesc.AddressV = d3dAddressMode;
	sampleDesc.AddressW = d3dAddressMode;
	sampleDesc.BorderColor[0] = 1.0f;
	sampleDesc.BorderColor[1] = 1.0f;
	sampleDesc.BorderColor[2] = 1.0f;
	sampleDesc.BorderColor[3] = 1.0f;
	sampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampleDesc.MinLOD = 0;
	sampleDesc.MaxLOD = D3D11_FLOAT32_MAX;

	auto device = GetDevice();
	auto hr = device->CreateSamplerState(&sampleDesc, &mSampler);

}

void Sampler::Terminate()
{
	SafeRelease(mSampler);
}

void Sampler::BindPS(uint32_t slot)
{
	GetContext()->PSSetSamplers(slot, 0, &mSampler);
}
