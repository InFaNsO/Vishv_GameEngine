#include "Precompiled.h"
#include "EditorRenderToWindow.h"
#include "Editor.h"
#include "GameWorld.h"

#include "Common.h"



void Vishv::Editor::RenderToWindow::Initialize()
{
	auto gs = Vishv::Graphics::GraphicsSystem::Get();
	mWindowHeight = static_cast<uint32_t>(gs->GetBackBufferHeight());
	mWindowWidth = static_cast<uint32_t>(gs->GetBackBufferWidth());

	mRenderTarget.Initialize(mWindowWidth, mWindowHeight,
		Vishv::Graphics::RenderTarget::Format::RGBA_U8);
}

void Vishv::Editor::RenderToWindow::Resize()
{
	mRenderTarget.Resize(mWindowWidth, mWindowHeight);
	ImVec2 vMin = ImGui::GetWindowContentRegionMin();
	ImVec2 vMax = ImGui::GetWindowContentRegionMax();


	mWindowWidth = static_cast<uint32_t>(vMax.x - vMin.x);
	mWindowHeight = static_cast<uint32_t>(vMax.y - vMin.y);
}

void Vishv::Editor::RenderToWindow::Resize(Math::Vector2 dimension)
{
	mWindowWidth = static_cast<uint32_t>(dimension.x);
	mWindowHeight = static_cast<uint32_t>(dimension.y);

	mRenderTarget.Resize(mWindowWidth, mWindowHeight);
}

void Vishv::Editor::RenderToWindow::DoUI()
{
	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::PostProcessing);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("PointWrap")->BindPS(0);
	mRenderTarget.BindPS();

	ImGui::Image(mRenderTarget.GetShaderResourceView(), { static_cast<float>(mWindowWidth), static_cast<float>(mWindowHeight)});
}

void Vishv::Editor::RenderToWindow::Terminate()
{
	mRenderTarget.Terminate();
}

