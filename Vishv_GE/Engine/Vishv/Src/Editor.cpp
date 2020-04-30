#include "Precompiled.h"
#include "Editor.h"

#include "GameWorld.h"
#include "GameObject.h"
/*
Vishv::EditorManager::EditorManager(GameWorld & world)
	:mWorld(world)
{
}

void Vishv::EditorManager::ShowWorldView()
{
	ImGui::Begin("World");

	if (ImGui::TreeNode("Services"))
	{
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Game Objects"))
	{
		for (auto gameObejct : mWorld.mUpdateList)
		{
			if (ImGui::Selectable(gameObejct->GetName()))
			{
				mCurrentGameObject = gameObejct; 
			}
		}

		ImGui::TreePop();
	}


	ImGui::End();

}

void Vishv::EditorManager::ShowInspectorView()
{
	ImGui::Begin("Inspector");

	if (!mCurrentGameObject)
	{
		ImGui::End();
		return;
	}

	ImGui::Text(mCurrentGameObject->mName.c_str());

	for (auto& comp : mCurrentGameObject->mComponents)
	{
		auto metaClass = comp->GetMetaClass();
		if (!ImGui::CollapsingHeader(metaClass->GetName()))
			continue;

		for (size_t i = 0; i < metaClass->GetFieldCount(); ++i)
		{
			auto metaField = metaClass->GetField(i);

			if (metaField->GetMetaType() == Core::Meta::DeduceType<int>())
			{
				int* data = (int*)(uint8_t)comp.get() + metaField->GetOffset();
				ImGui::DragInt(metaField->GetName(), data);
			}
			else if (metaField->GetMetaType() == Core::Meta::DeduceType<float>())
			{
				float* data = (float*)(uint8_t)comp.get() + metaField->GetOffset();
				ImGui::DragFloat(metaField->GetName(), data, 0.1f);
			}
			else if (metaField->GetMetaType() == Core::Meta::DeduceType<Math::Vector3>())
			{
				float* data = (float*)(uint8_t)comp.get() + metaField->GetOffset();
				ImGui::DragFloat3(metaField->GetName(), data, 0.1f);
			}
			else if (metaField->GetMetaType() == Core::Meta::DeduceType<Math::Quaternion>())
			{
				Math::Quaternion* data = (Math::Quaternion*)(uint8_t)comp.get() + metaField->GetOffset();
				ImGui::DragFloat3(metaField->GetName(), &data->x, 0.1f);
			}
		}
	}

	ImGui::End();
	
}*/

