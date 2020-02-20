#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "RapidJSON/Inc/document.h"
#include "RapidJSON/Inc/writer.h"
#include "RapidJSON/Inc/stringbuffer.h"



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

	//do rapid json parse

	return gameObject;
}

void Vishv::GameObjectFactory::Destroy(GameObject * gameObject)
{
}
