#include "Precompiled.h"
#include "MetaRegistration.h"

namespace Vishv::Core::Meta
{
	template<>
	void Deserialize<int>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(int*)(instance) = jsonValue.GetInt();
	}
	template<>
	void Deserialize<float>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(float*)(instance) = jsonValue.GetFloat();
	}
	template<>
	void Deserialize<bool>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(bool*)(instance) = jsonValue.GetBool();
	}
	template<>
	void Deserialize<std::string>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(std::string*)(instance) = jsonValue.GetString();
	}
	template<>
	void Deserialize<uint32_t>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(uint32_t*)(instance) = jsonValue.GetUint();
	}
	template<>
	void Deserialize<size_t>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(size_t*)(instance) = jsonValue.GetUint();
	}
}



using namespace Vishv;

//Primitive basic defeination
META_TYPE_DEFINE(int, Integer)
META_TYPE_DEFINE(float, Number)
META_TYPE_DEFINE(bool, Boolean)
META_TYPE_DEFINE(std::string, String)
META_TYPE_DEFINE(uint32_t, UInt)
META_TYPE_DEFINE(size_t, Size_t)

void Vishv::Core::StaticMetaRegister()
{

}

