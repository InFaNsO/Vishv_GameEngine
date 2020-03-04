
#include "Precompiled.h"
#include "GameObjectFactory.h"


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

	if (templateFileName.extension() != ".json")
		return gameObject;

	FILE* file = nullptr;
	if (fopen_s(&file, templateFileName.string().c_str(), "r") == EINVAL)
		return gameObject;
	

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
				auto newComp = gameObject->AddComponent(*metaClass);
				VISHVASSERT(newComp, "[Create] Component not found");
				metaClass->Deserialize(newComp, comp.value);
			}
		}
	}

	fclose(file);

	return gameObject;
}

void Vishv::GameObjectFactory::Destroy(GameObject * gameObject)
{
}
