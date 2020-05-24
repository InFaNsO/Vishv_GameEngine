#include "Precompiled.h"
#include "PostProcessService.h"

#include "PostProcessor.h"
#include "EditorRenderToWindow.h"

using namespace Vishv;

META_DERIVED_BEGIN(PostProcessService, Service)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END


void Vishv::PostProcessService::Initialize()
{
	mScreenMeshBuffer.Initialize(Graphics::Meshbuilder::CreateNDCQuad());
	mMainRT = std::make_unique<Editor::RenderToWindow>();
}

void Vishv::PostProcessService::RegisterProcessor(Components::PostProcessor& pp)
{
	myPostProcessor.push_back(&pp);
	myEffectsRT.emplace_back(std::move(std::make_unique<Editor::RenderToWindow>()))->Initialize();
}


void Vishv::PostProcessService::Render()
{
	using namespace Graphics;

	if (myPostProcessor.size() == 0)
		return;

	auto prvRt = myPostProcessor[0]->GetFinalRenderTarget();
	auto em = EffectsManager::Get();
	em->BindBuffer(EffectType::Merge);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("PointWrap")->BindPS(0);

	for (size_t i = 1; i < myEffectsRT.size(); ++i)
	{
		if(i > 1)


		auto rt = myPostProcessor[i]->GetFinalRenderTarget();

		myEffectsRT[i]->BeginRender();
		prvRt->BindTexture(0);
		rt->BindTexture(1);
		mScreenMeshBuffer.Render();

	}
}
