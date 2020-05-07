#include "Precompiled.h"
#include "GameObject.h"
#include "Component.h"
#include "GameWorld.h"

#include "ModelAnimation.h"

#include "Editor.h"

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

void Vishv::GameObject::Update()
{
	if (!mIsActive)
		return;

	for (auto& component : mComponents)
		component->Update();
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

	ImGui::Checkbox("", &mIsActive);
	ImGui::SameLine();
	ImGui::Text(mName.c_str());
	for (auto& component : mComponents)
	{
		auto comp = component.get()->GetMetaClass();
		if (ImGui::CollapsingHeader(comp->GetName()))
		{
			auto mclass = comp;
			for (size_t i = 0; i < comp->GetFieldCount(); ++i)
			{
				void* me = component.get();
				auto field = mclass->GetField(i);

				if (field->GetMetaType()->GetCategory() == Core::Meta::MetaType::Category::Primitive)
				{
					void* data = static_cast<uint8_t*>(me) + field->GetOffset();
					if (field->GetMetaType()->GetName() == std::string("Number"))
						ImGui::DragFloat(field->GetName(), static_cast<float*>(data));
					else if (field->GetMetaType()->GetName() == std::string("Integer") || field->GetMetaType()->GetName() == std::string("UInt") || field->GetMetaType()->GetName() == std::string("Size_t"))
						ImGui::DragInt(field->GetName(), static_cast<int*>(data));
					else if (field->GetMetaType()->GetName() == std::string("Boolean"))
						ImGui::Checkbox(field->GetName(), static_cast<bool*>(data));
					else if (field->GetMetaType()->GetName() == std::string("String"))
					{
						auto s = static_cast<std::string*>(data);
						s->reserve(256);
						ImGui::InputText(field->GetName(), s->data(), s->max_size());
					}
					else if (field->GetMetaType()->GetName() == std::string("Vector2"))
					{
						ImGui::DragFloat3(field->GetName(), &static_cast<Math::Vector2*>(data)->x);
					}
					else if (field->GetMetaType()->GetName() == std::string("Vector3"))
					{
						ImGui::DragFloat3(field->GetName(), &static_cast<Math::Vector3*>(data)->x);
					}
					else if (field->GetMetaType()->GetName() == std::string("Vector4"))
					{
						ImGui::ColorEdit4(field->GetName(), &static_cast<Math::Vector4*>(data)->r);
					}
					else if (field->GetMetaType()->GetName() == std::string("Quaternion"))
					{
						Math::Quaternion* quat = static_cast<Math::Quaternion*>(data);

						Math::Vector3 xyz;
						xyz.x = quat->GetRotation(Math::Vector3(1.0f, 0.0f, 0.0f)) * Math::Constans::RadToDeg;
						xyz.y = quat->GetRotation(Math::Vector3(0.0f, 1.0f, 0.0f)) * Math::Constans::RadToDeg;
						xyz.z = quat->GetRotation(Math::Vector3(0.0f, 0.0f, 1.0f)) * Math::Constans::RadToDeg;

						auto copy = xyz;
						if (ImGui::DragFloat3(field->GetName(), &xyz.x))
						{
							if (xyz.x != copy.x)
								*quat *= Math::Quaternion::RotationQuaternion(xyz.x * Math::Constans::DegToRad, Math::Vector3(1.0f, 0.0f, 0.0f));
							else if (xyz.y != copy.y)
								*quat *= Math::Quaternion::RotationQuaternion(xyz.y * Math::Constans::DegToRad, Math::Vector3(0.0f, 1.0f, 0.0f));
							else if (xyz.z != copy.z)
								*quat *= Math::Quaternion::RotationQuaternion(xyz.z * Math::Constans::DegToRad, Math::Vector3(0.0f, 0.0f, 1.0f));
						}

					}
				}
			}
			component->DebugUI();
		}
	}

	ImGui::InputText("Component Name", &componentName[0], 256);
	if (ImGui::Button("AddComponent"))
	{
		auto metaClass = Core::Meta::FindMetaClass(componentName);
		auto ptr = AddComponent(*metaClass);
		VISHVASSERT(ptr, "[Game Object] Component not found");
		ptr->Initialize();

		memset(componentName, 0, 256);
	}
}

void Vishv::GameObject::SimpleDraw()
{
	if (!mIsActive)
		return;

	for (auto& component : mComponents)
		component->SimpleDraw();
}


Vishv::Components::Component* Vishv::GameObject::AddComponent(const Core::Meta::MetaClass& metaClass)
{
	Components::Component* comp = static_cast<Components::Component*>(metaClass.Create());
	comp->mOwner = this;
	mComponents.emplace_back(std::move(comp));
	return mComponents[mComponents.size() - 1].get();
}
