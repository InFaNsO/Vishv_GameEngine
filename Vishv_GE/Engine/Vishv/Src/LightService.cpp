#include "Precompiled.h"
#include "LightService.h"

using namespace Vishv;

META_DERIVED_BEGIN(Lighting, Service)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END


void Vishv::Lighting::Initialize()
{
	SetName("Lighting");
	em = Graphics::EffectsManager::Get();
	mLightData.position_Direction = { 1.f, -1.f, 1.f };
	mLightData.position_Direction.Normalize();
}

void Vishv::Lighting::DebugUI()
{
	//show Light controls
	if (ImGui::CollapsingHeader("Light"))
	{
		bool changed = false;
		if (ImGui::DragFloat3("Direction X##Light", &mLightData.position_Direction.x, 0.01f, -1.0f, 1.0f))
		{
			mLightData.position_Direction.Normalize();
		}
		ImGui::ColorEdit4("Ambient##Light", &mLightData.ambient.x);
		ImGui::ColorEdit4("Diffuse##Light", &mLightData.diffuse.x);
		ImGui::ColorEdit4("Specular##Light", &mLightData.specular.x);
	}
		//show Material controls
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::ColorEdit4("Ambient##Material", &mMaterialData.ambient.x);
		ImGui::ColorEdit4("Diffuse##Material", &mMaterialData.diffuse.x);
		ImGui::ColorEdit4("Specular##Material", &mMaterialData.specular.x);
		ImGui::DragFloat("Power##Material", &mMaterialData.power);
	}

	if (ImGui::CollapsingHeader("Options"))
	{
		ImGui::DragFloat("var 1", &mOptionsData.variable1);
		ImGui::DragFloat("var 2", &mOptionsData.variable2);
		ImGui::DragFloat("var 3", &mOptionsData.variable3);
		ImGui::DragFloat("var 4", &mOptionsData.variable4);
	}
}

void Vishv::Lighting::Bind(Graphics::EffectType type)
{
	if (Vishv::Graphics::EffectsManager::Get()->GetBufferType(type) & Vishv::Graphics::EffectBufferType::EBTYPE_LIGHT)
		em->GetBufferData(type)->SetLight(mLightData);

	if (Vishv::Graphics::EffectsManager::Get()->GetBufferType(type) & Vishv::Graphics::EffectBufferType::EBTYPE_MATERIAL)
		em->GetBufferData(type)->SetMaterial(mMaterialData);

	if (Vishv::Graphics::EffectsManager::Get()->GetBufferType(type) & Vishv::Graphics::EffectBufferType::EBTYPE_OPTIONS)
		em->GetBufferData(type)->SetOptions(mOptionsData);
}

