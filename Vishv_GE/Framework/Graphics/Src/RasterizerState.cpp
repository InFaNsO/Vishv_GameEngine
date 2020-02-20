#include "Precompiled.h"
#include "RasterizerState.h"
#include "D3DUtil.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	D3D11_CULL_MODE GetCullMode(RasterizerState::CullMode mode)
	{
		switch (mode)
		{
		case Vishv::Graphics::RasterizerState::CullMode::Front:
			return D3D11_CULL_FRONT;
			break;
		case Vishv::Graphics::RasterizerState::CullMode::Back:
			return D3D11_CULL_BACK;
			break;
		case Vishv::Graphics::RasterizerState::CullMode::None:
			return D3D11_CULL_NONE;
			break;
		default:
			return D3D11_CULL_BACK;
			break;
		}
	}
	D3D11_FILL_MODE GetFillMode(RasterizerState::FillMode mode)
	{
		switch (mode)
		{
		case Vishv::Graphics::RasterizerState::FillMode::Solid:
			return D3D11_FILL_SOLID;
			break;
		case Vishv::Graphics::RasterizerState::FillMode::Wireframe:
			return D3D11_FILL_WIREFRAME;
			break;
		default:
			return D3D11_FILL_SOLID;
			break;
		}
	}
}

Vishv::Graphics::RasterizerState::~RasterizerState()
{
	VISHVASSERT(mRasteriserState == nullptr, "[RasterizerState] Rasterizer not released.");
}

void Vishv::Graphics::RasterizerState::Initialize(CullMode cMode, FillMode fMode)
{
	D3D11_RASTERIZER_DESC desc{};
	desc.CullMode = GetCullMode(cMode);
	desc.FillMode = GetFillMode(fMode);
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	HRESULT hr = GetDevice()->CreateRasterizerState(&desc, &mRasteriserState);
	VISHVASSERT(SUCCEEDED(hr), "[RasterizerState] Failed to create rasterizer state");
}

void Vishv::Graphics::RasterizerState::Terminate()
{
	mRasteriserState->Release();
	SafeRelease<ID3D11RasterizerState>(mRasteriserState);
}

void Vishv::Graphics::RasterizerState::Set()
{
	GetContext()->RSSetState(mRasteriserState);
}

void Vishv::Graphics::RasterizerState::Clear()
{
	GetContext()->RSSetState(nullptr);
}

