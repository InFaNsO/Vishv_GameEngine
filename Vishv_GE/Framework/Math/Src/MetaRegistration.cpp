#include "Precompiled.h"
#include "MetaRegistration.h"

namespace Vishv::Core::Meta
{
	template<>
	void Deserialize<Math::Vector2>(void* instance, const rapidjson::Value& jsonValue)
	{
		auto object = jsonValue.GetObjectW();
		auto vec = (Math::Vector2*)(instance);
		vec->x = object.FindMember("x")->value.GetFloat();
		vec->y = object.FindMember("y")->value.GetFloat();
	}
	template<>
	void Deserialize<Math::Vector3>(void* instance, const rapidjson::Value& jsonValue)
	{
		auto object = jsonValue.GetObjectW();
		auto vec = (Math::Vector3*)(instance);
		vec->x = object.FindMember("x")->value.GetFloat();
		vec->y = object.FindMember("y")->value.GetFloat();
		vec->z = object.FindMember("z")->value.GetFloat();
	}

	template<>
	void Deserialize<Math::Vector4>(void* instance, const rapidjson::Value& jsonValue)
	{
		auto object = jsonValue.GetObjectW();
		auto vec = (Math::Vector4*)(instance);
		vec->x = object.FindMember("x")->value.GetFloat();
		vec->y = object.FindMember("y")->value.GetFloat();
		vec->z = object.FindMember("z")->value.GetFloat();
		vec->w = object.FindMember("w")->value.GetFloat();
	}

	template<>
	void Deserialize<Math::Quaternion>(void* instance, const rapidjson::Value& jsonValue)
	{
		auto object = jsonValue.GetObjectW();
		auto quat = (Math::Quaternion*)(instance);
		quat->x = object.FindMember("x")->value.GetFloat();
		quat->y = object.FindMember("y")->value.GetFloat();
		quat->z = object.FindMember("z")->value.GetFloat();
		quat->w = object.FindMember("w")->value.GetFloat();
	}
}


//Primitive basic defeination
META_TYPE_DEFINE(Vishv::Math::Vector2, Vector2)
META_TYPE_DEFINE(Vishv::Math::Vector3, Vector3)
META_TYPE_DEFINE(Vishv::Math::Vector4, Vector4)

META_TYPE_DEFINE(Vishv::Math::Quaternion, Quaternion)

void Vishv::Math::StaticMetaRegister()
{
//	META_REGISTER(Vector3);
	META_REGISTER(Transform);
}

