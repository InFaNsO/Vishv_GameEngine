#include "Precompiled.h"
#include "GameObject.h"
#include "Component.h"
#include "GameWorld.h"

#include "ModelAnimation.h"

using namespace Vishv;

META_CLASS_BEGIN(GameObject)
META_NO_FIELD
META_CLASS_END


void Vishv::GameObject::Initialize()
{
	for (auto& component : mComponents)
		component->Initialize();
}

void Vishv::GameObject::Terminate()
{
	for (auto& component : mComponents)
		component->Terminate();
}

void Vishv::GameObject::Update(float deltaTime)
{
	if (!mIsActive)
		return;

	for (auto& component : mComponents)
		component->Update(deltaTime);
}

void Vishv::GameObject::Render()
{
	if (!mIsActive)
		return;

	for (auto& component : mComponents)
		component->Render();
}

void Vishv::GameObject::DebugUI()
{
	if (!mIsActive)
		return;

	for (auto& component : mComponents)
	{
		if (component->StaticGetMetaClass()->GetName() == Vishv::Components::ModelAnimation::StaticGetMetaClass()->GetName())
		{
			if (ImGui::CollapsingHeader(component->StaticGetMetaClass()->GetName()))
			{

			}
		}
		else
			component->DebugUI();
	}
}

void Vishv::GameObject::SimpleDraw()
{
	if (!mIsActive)
		return;

	for (auto& component : mComponents)
		component->SimpleDraw();
}
