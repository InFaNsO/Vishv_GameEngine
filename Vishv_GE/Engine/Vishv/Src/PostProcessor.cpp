#include "Precompiled.h"
#include "PostProcessor.h"
#include "PostProcessService.h"
#include "EditorRenderToWindow.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "Editor.h"

#include "Model3D.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(PostProcessor, Component)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END

namespace
{
	using namespace Graphics;
	std::string EnumToString(EffectType type)
	{
		switch (type)
		{
		case Vishv::Graphics::EffectType::Blur:
			return "Blur";
			break;
		case Vishv::Graphics::EffectType::DoLighting:
			return "DoLighting";
			break;
		case Vishv::Graphics::EffectType::DoNothing:
			return  "DoNothing";
			break;
		case Vishv::Graphics::EffectType::DoSomething:
			return  "DoSomething";
			break;
		case Vishv::Graphics::EffectType::Merge:
			return  "Merge";
			break;
		case Vishv::Graphics::EffectType::Particle:
			return  "Particle";
			break;
		case Vishv::Graphics::EffectType::PostProcessing:
			return  "PostProcessing";
			break;
		case Vishv::Graphics::EffectType::SimpleDraw:
			return  "SimpleDrawShader";
			break;
		case Vishv::Graphics::EffectType::Skinning:
			return  "Skining";
			break;
		case Vishv::Graphics::EffectType::Standard:
			return  "Standard";
			break;
		case Vishv::Graphics::EffectType::Texturing:
			return  "Texturing";
			break;
		case Vishv::Graphics::EffectType::Mixamo:
			return  "Mixamo";
			break;
		case Vishv::Graphics::EffectType::CellShader:
			return  "CellShader";
			break;
		default:
			return "wrong input";
			break;
		}
	}
}


void Vishv::Components::PostProcessor::Initialize()
{
	myModel = GetOwner().GetComponent<Model3D>();
	PPservice = GetOwner().GetWorld().GetService<PostProcessService>();

	AddEffect(Graphics::EffectType::Skinning);

	mScreenMeshBuffer.Initialize(Graphics::Meshbuilder::CreateNDCQuad());
}

void Vishv::Components::PostProcessor::Update()
{
	return;

	auto dimension = EditorManager::Get()->GetRenderSpace();
	for (int i = 0; i < (size_t)myEffects.size(); ++i)
	{
		using namespace Graphics;
		switch (myEffects[i])
		{
		case EffectType::CellShader:
			UpdateCellShader(i);

		default:
			break;
		}
		myEffectsRT[i]->Resize(dimension);
	}
}

void Vishv::Components::PostProcessor::UpdateCellShader(int index)
{
	auto space = EditorManager::Get()->GetRenderSpace();
	mEffectOptions[index].variable1 = 1.f /space.x;
	mEffectOptions[index].variable2 = 1.f /space.y;
}

void Vishv::Components::PostProcessor::DebugUI()
{
	static std::string currentItem = "";
	static int selectedIndex = -1;
	bool isSelected = false;
	if (ImGui::BeginCombo("##EffectCombo", currentItem.c_str()))
	{
		using namespace Graphics;
		for (size_t i = 0; i < (int)EffectType::Count; ++i)
		{
			isSelected = (currentItem == EnumToString(static_cast<EffectType>(i)));
			if (ImGui::Selectable(EnumToString(static_cast<EffectType>(i)).c_str(), isSelected))
				currentItem = EnumToString(static_cast<EffectType>(i)).c_str();
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
				selectedIndex = static_cast<int>(i);
			}
		}
		ImGui::EndCombo();
	}

	if (ImGui::Button("Set##PP") && selectedIndex >= 0)
	{
		AddEffect(static_cast<Graphics::EffectType>(selectedIndex));
	}

	for (int i = 0; i < (size_t)myEffects.size(); ++i)
	{
		using namespace Graphics;
		switch (myEffects[i])
		{
		case EffectType::CellShader:
			UICellShader(i);

		default:
			break;
		}
	}
}
void Vishv::Components::PostProcessor::UICellShader(int index)
{
	if (true)// !ImGui::CollapsingHeader(Graphics::ToString(myEffects[index]).c_str()))
		return;

	ImGui::DragFloat(": Threshold", &mEffectOptions[index].variable3, 0.01f, 0.0f, 1.0f);

}

void Vishv::Components::PostProcessor::AddEffect(Graphics::EffectType effect)
{
	if (Graphics::EffectType::Count == effect)
		return;


	MyEffects |= static_cast<int>(effect);
	
	/*
	myEffects.push_back(effect);
	mEffectOptions.push_back(Graphics::EffectBufferType::OptionsData());
	myEffectsRT.emplace_back(std::move(std::make_unique<Editor::RenderToWindow>()))->Initialize();
	*/
}

void Vishv::Components::PostProcessor::CustomRender(Graphics::EffectType effect)
{
	//call the private function for this effect
	switch (effect)
	{
	case Vishv::Graphics::EffectType::Blur:
		break;
	case Vishv::Graphics::EffectType::DoLighting:
		break;
	case Vishv::Graphics::EffectType::DoNothing:
		break;
	case Vishv::Graphics::EffectType::DoSomething:
		break;
	case Vishv::Graphics::EffectType::Merge:
		break;
	case Vishv::Graphics::EffectType::Particle:
		break;
	case Vishv::Graphics::EffectType::PostProcessing:
		break;
	case Vishv::Graphics::EffectType::SimpleDraw:
		break;
	case Vishv::Graphics::EffectType::Skinning:
		RenderSkinning();
		break;
	case Vishv::Graphics::EffectType::Standard:
		break;
	case Vishv::Graphics::EffectType::Texturing:
		break;
	case Vishv::Graphics::EffectType::Mixamo:
		break;
	case Vishv::Graphics::EffectType::CellShader:
		break;
	default:
		break;
	}

}

void Vishv::Components::PostProcessor::RenderSkinning()
{
	if (!myModel->mModel || myModel->mShowSkeleton)
		return;
	myModel->Render();
}

/*
void Vishv::Components::PostProcessor::Render()
{
	return;

	if (!myModel->mModel || myModel->mShowSkeleton)
		return;

	myEffectsRT[0]->BeginRender();
	myModel->Render();
	myEffectsRT[0]->EndRender();
	
	Vishv::Graphics::SamplerManager::Get()->GetSampler("PointWrap")->BindPS(0);

	auto em = Vishv::Graphics::EffectsManager::Get();

	for (size_t i = 1; i < myEffects.size(); ++i)
	{
		myEffectsRT[i]->BeginRender();
		em->BindEffect(myEffects[i]);
		em->GetBufferData(myEffects[i])->SetOptions(mEffectOptions[i]);
		myEffectsRT[i - 1]->BindTexture();
		mScreenMeshBuffer.Render();
		myEffectsRT[i]->EndRender();
	}
}
*/
Editor::RenderToWindow* Vishv::Components::PostProcessor::GetFinalRenderTarget()
{
	return myEffectsRT.size() > 0 ? myEffectsRT[myEffectsRT.size() - 1].get() : nullptr;
}

