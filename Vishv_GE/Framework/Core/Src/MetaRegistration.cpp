#include "Precompiled.h"
#include "MetaRegistration.h"

namespace Vishv::Core::Meta
{
	template<> void Deserialize<int>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(int*)(instance) = jsonValue.GetInt();
	}
	template<> void Serialize<int>(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc)
	{
	}

	template<> void Deserialize<float>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(float*)(instance) = jsonValue.GetFloat();
	}
	template<> void Serialize<float>(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc)
	{
		jsonValue.SetFloat(*(float*)(instance));
	}

	template<> void Deserialize<bool>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(bool*)(instance) = jsonValue.GetBool();
	}
	template<> void Serialize<bool>(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc)
	{
		jsonValue.SetBool(*(bool*)(instance));
	}

	template<> void Deserialize<std::string>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(std::string*)(instance) = jsonValue.GetString();
	}
	template<> void Serialize<std::string>(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc)
	{
		//auto s = (std::string*)(instance);
		//jsonValue.SetString(s->c_str(), s->length());
	}

	template<> void Deserialize<uint32_t>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(uint32_t*)(instance) = jsonValue.GetUint();
	}
	template<> void Serialize<uint32_t>(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc)
	{
		jsonValue.SetUint(*(uint32_t*)(instance));
	}

	template<> void Deserialize<uint64_t>(void* instance, const rapidjson::Value& jsonValue)
	{
		*(uint64_t*)(instance) = jsonValue.GetUint();
	}
	template<> void Serialize<uint64_t>(const void* instance, rapidjson::Value& jsonValue, rapidjson::Document& doc)
	{
		jsonValue.SetUint64(*(uint64_t*)(instance));
	}
}



using namespace Vishv;

//Primitive basic defeination
META_TYPE_DEFINE(int, Integer)
META_TYPE_DEFINE(float, Number)
META_TYPE_DEFINE(bool, Boolean)
META_TYPE_DEFINE(std::string, String)
META_TYPE_DEFINE(uint32_t, UInt)
META_TYPE_DEFINE(uint64_t, Size_t)

void Vishv::Core::StaticMetaRegister()
{

}

