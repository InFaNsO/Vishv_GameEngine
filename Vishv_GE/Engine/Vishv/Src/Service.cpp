#include "Precompiled.h"
#include "Service.h"

#include "GameWorld.h"

META_CLASS_BEGIN(Vishv::Service)
	META_NO_FIELD
META_CLASS_END


void Vishv::Service::DoUI(void* instance, const Core::Meta::MetaClass& mclass)
{
	for (size_t i = 0; i < mclass.GetFieldCount(); ++i)
	{
		void* me = instance;
		auto field = mclass.GetField(i);

		if (field->GetMetaType()->GetCategory() == Core::Meta::MetaType::Category::Primitive)
		{
			void* data = static_cast<uint8_t*>(me) + field->GetOffset();
			if (field->GetMetaType()->GetName() == "Number")
				ImGui::DragFloat(field->GetName(), static_cast<float*>(data));
			else if (field->GetMetaType()->GetName() == "Integer" || field->GetMetaType()->GetName() == "UInt" || field->GetMetaType()->GetName() == "Size_t")
				ImGui::DragInt(field->GetName(), static_cast<int*>(data));
			else if (field->GetMetaType()->GetName() == "Boolean")
				ImGui::Checkbox(field->GetName(), static_cast<bool*>(data));
			else if (field->GetMetaType()->GetName() == "String")
			{
				auto s = static_cast<std::string*>(data);
				s->reserve(256);
				ImGui::InputText(field->GetName(), s->data(), s->max_size());
			}
			else if (field->GetMetaType()->GetName() == "Vector2")
			{
				ImGui::DragFloat3(field->GetName(), &static_cast<Math::Vector2*>(data)->x);
			}
			else if (field->GetMetaType()->GetName() == "Vector3")
			{
				ImGui::DragFloat3(field->GetName(), &static_cast<Math::Vector3*>(data)->x);
			}
			else if (field->GetMetaType()->GetName() == "Vector4")
			{
				ImGui::ColorEdit4(field->GetName(), &static_cast<Math::Vector4*>(data)->r);
			}
			else if (field->GetMetaType()->GetName() == "Quaternion")
			{
				ImGui::Text(field->GetName());
				Math::Quaternion* quat = static_cast<Math::Quaternion*>(data);

				Math::Vector3 xyz;
				xyz.x = quat->GetRotation(Math::Vector3(1.0f, 0.0f, 0.0f)) * Math::Constans::RadToDeg;
				xyz.y = quat->GetRotation(Math::Vector3(0.0f, 1.0f, 0.0f)) * Math::Constans::RadToDeg;
				xyz.z = quat->GetRotation(Math::Vector3(0.0f, 0.0f, 1.0f)) * Math::Constans::RadToDeg;

				auto copy = xyz;
				if (ImGui::DragFloat3(field->GetName, &xyz.x))
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
}

