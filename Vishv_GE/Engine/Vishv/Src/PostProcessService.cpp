#include "Precompiled.h"
#include "PostProcessService.h"

#include "GameWorld.h"
#include "SkyBoxService.h"
#include "SimpleDrawService.h"
#include "LightService.h"

#include "PostProcessor.h"
#include "EditorRenderToWindow.h"
#include "Editor.h"


using namespace Vishv;

META_DERIVED_BEGIN(PostProcessService, Service)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END


void Vishv::PostProcessService::Initialize()
{
	SetName("Post Processing");

	mScreenMeshBuffer.Initialize(Graphics::Meshbuilder::CreateNDCQuad());
	mMainRT = std::make_unique<Editor::RenderToWindow>();

	mSkyBox = GetWorld().GetService<SkyBox>();
	mSimpleDraw = GetWorld().GetService<SimpleDrawer>();
	mLighting = GetWorld().GetService<Lighting>();
}

void Vishv::PostProcessService::RegisterProcessor(Components::PostProcessor& pp)
{
	myPostProcessor.push_back(&pp);
	//myEffectsRT.emplace_back(std::move(std::make_unique<Editor::RenderToWindow>()))->Initialize();
}


void Vishv::PostProcessService::Render()
{
	using namespace Graphics;
	
	auto editor = EditorManager::Get();
	auto effect = EffectsManager::Get();
	
	editor->BeginSceneRender();

	mSkyBox->Render();
	
	for (int i = 0; i < static_cast<int>(EffectType::Count); ++i)
	{
		int effectNum = 0x1 << i;
		mCurrentEffect = static_cast<EffectType>(effectNum);
		effect->BindEffect(mCurrentEffect);
		if (mCurrentEffect == EffectType::Skinning || mCurrentEffect == EffectType::CellShader)
			mLighting->Bind(mCurrentEffect);
		for (size_t j = 0; j < myPostProcessor.size(); ++j)
		{
			if (myPostProcessor[j]->MyEffects & effectNum)
				myPostProcessor[j]->GetOwner().Render();
		}
	}

	GetWorld().SimpleDraw();
	mSimpleDraw->Render();

	editor->EndSceneRender();

	return;
	/*auto prvRt = myPostProcessor[0]->GetFinalRenderTarget();
	auto em = EffectsManager::Get();
	em->BindBuffer(EffectType::Merge);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("PointWrap")->BindPS(0);

	for (size_t i = 1; i < myEffectsRT.size(); ++i)
	{
		if (i > 1)
		{

		}

		auto rt = myPostProcessor[i]->GetFinalRenderTarget();

		myEffectsRT[i]->BeginRender();
		prvRt->BindTexture(0);
		rt->BindTexture(1);
		mScreenMeshBuffer.Render();

	}*/
}
