#include "Precompiled.h"
#include "SpriteRenderer.h"

#include "D3DUtil.h"

#include "GraphicsSystem.h"
#include "DirectXTK/Inc/SpriteBatch.h"
#include "Texture.h"

using namespace Vishv::Graphics;
using namespace Vishv::Math;

namespace
{
	std::unique_ptr<SpriteRenderer> sSpriteRenderer = nullptr;
}

void Vishv::Graphics::SpriteRenderer::StaticInitialize()
{
	VISHVASSERT(sSpriteRenderer == nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] System already initialized.");

	sSpriteRenderer = std::make_unique<SpriteRenderer>();
	sSpriteRenderer->Initialize();
}

void Vishv::Graphics::SpriteRenderer::StaticTerminate()
{
	if (sSpriteRenderer != nullptr)
	{
		sSpriteRenderer->Terminate();
		sSpriteRenderer = nullptr;
	}
}

SpriteRenderer * Vishv::Graphics::SpriteRenderer::Get()
{
	VISHVASSERT(sSpriteRenderer != nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] No instance created.");

	return sSpriteRenderer.get();
}


Vishv::Graphics::SpriteRenderer::~SpriteRenderer()
{
	VISHVASSERT(sSpriteRenderer == nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] Renderer not freed.");
}

void Vishv::Graphics::SpriteRenderer::Initialize()
{
	VISHVASSERT(mSpriteBatch == nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] Already Initialized");
	auto context = GetContext();
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
}

void Vishv::Graphics::SpriteRenderer::Terminate()
{
	VISHVASSERT(mSpriteBatch != nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] Already Terminated");
	mSpriteBatch.reset();
}

void Vishv::Graphics::SpriteRenderer::BeginRender()
{
	VISHVASSERT(mSpriteBatch != nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] Not Initialized");
	mSpriteBatch->Begin();
}

void Vishv::Graphics::SpriteRenderer::EndRender()
{
	VISHVASSERT(mSpriteBatch != nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] Not Initialized");
	mSpriteBatch->End();
}

void Vishv::Graphics::SpriteRenderer::Draw(const Texture & texture, const Vishv::Math::Vector2 & pos)
{
	VISHVASSERT(mSpriteBatch != nullptr, "[Vishv::Graphics::SpriteRenderer::StaticInitialize] Not Initialized");
	mSpriteBatch->Draw( GetShaderResourceView(texture), DirectX::XMFLOAT2{ pos.x, pos.y });
}

	