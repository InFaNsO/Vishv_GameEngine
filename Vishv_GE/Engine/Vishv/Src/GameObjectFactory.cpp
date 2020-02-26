#include "Precompiled.h"
#include "GameObjectFactory.h"
#include <RapidJSON/Inc/document.h>
#include <RapidJSON/Inc/filereadstream.h>



namespace
{
	void Deserialize(void* instance, const Vishv::Core::Meta::MetaType* metaType, const rapidjson::Value& jsonValue)
	{

	}

	void Deserialize(void* instance, const Vishv::Core::Meta::MetaPointer* metaPointer, const rapidjson::Value& jsonValue)
	{

	}

	void Deserialize(void* instance, const Vishv::Core::Meta::MetaArray* metaArray, const rapidjson::Value& jsonValue)
	{

	}

	void Deserialize(void* instance, const Vishv::Core::Meta::MetaClass* metaClass, const rapidjson::Value& jsonValue)
	{
		for (auto& prop : jsonValue.GetObjectW())
		{
			auto metaField = metaClass->FindField(prop.name.GetString());

			auto instanceField = static_cast<uint8_t*>(instance) + metaField->GetOffset();

			switch (metaField->GetMetaType()->GetCategory())
			{
			case Vishv::Core::Meta::MetaType::Category::Primitive:
				Deserialize(instanceField, metaField->GetMetaType(), prop.value);
				break;
			case Vishv::Core::Meta::MetaType::Category::Pointer:
				Deserialize(instanceField, metaField->GetMetaType()->GetMetaPointer(), prop.value);
				break;
			case Vishv::Core::Meta::MetaType::Category::Class:
				Deserialize(instanceField, metaField->GetMetaType()->GetMetaClass(), prop.value); 
				break;
			case Vishv::Core::Meta::MetaType::Category::Array:
				Deserialize(instanceField, metaField->GetMetaType()->GetMetaArray(), prop.value);
				break;
			default:
				break;
			}

		}
	}
}


using namespace Vishv;




Vishv::GameObjectFactory::GameObjectFactory(GameObjectAllocator & allocator)
	:mGameObjectAllocator(allocator)
{
}

GameObject * Vishv::GameObjectFactory::Create(const std::filesystem::path& templateFileName)
{
	GameObject* gameObject = mGameObjectAllocator.New();
	if (gameObject == nullptr)
		return gameObject;

	FILE* file = nullptr;
	fopen_s(&file, templateFileName.string().c_str(), "r");

	using namespace rapidjson;

	//do rapid json parse

	char readbuffer[65536];
	FileReadStream is(file, readbuffer, sizeof(readbuffer));

	Document doc;
	doc.ParseStream(is);
	if (doc.HasMember("GameObject") && doc["GameObject"].IsObject())
	{
		auto jsonObj = doc["GameObject"].GetObjectW();
		if (jsonObj.HasMember("Components") && jsonObj["Components"].IsObject())
		{
			auto comps = jsonObj["Components"].GetObjectW();
			for (auto& comp : comps)
			{
				auto metaClass = Core::Meta::FindMetaClass(comp.name.GetString());
				auto comp = gameObject->AddComponent(*metaClass);

				VISHVASSERT(comp, "[Create] Component not found");
			}
		}
	}

	fclose(file);

	return gameObject;
}

void Vishv::GameObjectFactory::Destroy(GameObject * gameObject)
{
}
