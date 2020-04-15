#include "Precompiled.h"
#include "GameWorld.h"
#include "GameObject.h"

#include "Editor.h"

using namespace Vishv;

////////////////////////////////////////////////////////////////////////////

void Vishv::GameWorld::Initialize(size_t capacity)
{
	VISHVASSERT(!mIsInitialized, "[GameWorld] world already initialized");

	mGameObjectAllocator = std::make_unique<Vishv::GameObjectAllocator>(capacity);
	mGameObjectHandlePool = std::make_unique<Vishv::GameObjectHandlePool>(static_cast<uint32_t>(capacity));
	mGameObjectFactory = std::make_unique<Vishv::GameObjectFactory>(*mGameObjectAllocator);

	for (auto& service : mServices)
		service->Initialize();

	mIsInitialized = true;
}

void Vishv::GameWorld::Terminate()
{
	if (!mIsInitialized)
		return;

	VISHVASSERT(!mIsUpdating, "Cannot terminate while updateing");

	std::for_each(mUpdateList.begin(), mUpdateList.end(), [this](auto gameObject)
	{
		Destroy(gameObject->GetHandle());
	});
	mUpdateList.clear();
	mIsUpdating = false;
	
	ProcessDestroyList();

	for (auto& service : mServices)
		service->Terminate();

	mGameObjectFactory.reset();
	mGameObjectAllocator.reset();
	mGameObjectHandlePool.reset();

	mIsInitialized = false;
}

void Vishv::GameWorld::Update(float deltaTime)
{
	VISHVASSERT(!mIsUpdating, "Already Updateing");

	for (auto& service : mServices)
		service->Update(deltaTime);

	mIsUpdating = true;

	for (size_t i = 0; i < mUpdateList.size(); ++i)
	{
		auto go = mUpdateList[i];
		if (go->mHandle.IsValid())
			go->Update(deltaTime);
	}

	mIsUpdating = false;

	ProcessDestroyList();
}

void Vishv::GameWorld::SimpleDraw()
{
	for (auto gameObject : mUpdateList)
		gameObject->SimpleDraw();
}

void Vishv::GameWorld::DebugUI()
{


	//add services
	//for (auto& service : mServices)
	//	service->Terminate();
}

void Vishv::GameWorld::Render()
{
	for (auto& service : mServices)
		service->Render();

	for (auto gameObject : mUpdateList)
		gameObject->Render();
}




GameObjectHandle Vishv::GameWorld::Create(const std::filesystem::path& templateFileName, std::string name)
{
	auto gameObject = mGameObjectFactory->Create(templateFileName);

	VISHVASSERT(gameObject != nullptr, "Cannot open the template");

	GameObjectHandle handle = mGameObjectHandlePool->Register(gameObject);

	gameObject->mWorld = this;
	gameObject->mHandle = handle;
	gameObject->mName = name;
	//gameObject->Initialize();

	mUpdateList.push_back(gameObject);
	return handle;
}

GameObjectHandle Vishv::GameWorld::Find(const std::string& name)
{
	using namespace std;
	auto iter = find_if(begin(mUpdateList), end(mUpdateList), [&name](auto gameObject)
	{
		return gameObject->GetName() == name;
	});

	return iter != end(mUpdateList) ? (*iter)->GetHandle() : GameObjectHandle();
}

void Vishv::GameWorld::Destroy(GameObjectHandle handle)
{
	if (!handle.IsValid())
		return;

	GameObject* go = handle.Get();
	mGameObjectHandlePool->UnRegister(handle);

	if (!mIsUpdating)
		DestroyInternal(go);
	else
		mDestroyList.push_back(go);
}

void Vishv::GameWorld::DestroyInternal(GameObject * gameObject)
{
	VISHVASSERT(mIsUpdating == false, "Game is updateing cant destroy object");

	if (gameObject == nullptr)
		return;

	auto iter = std::find(mUpdateList.begin(), mUpdateList.end(), gameObject);
	if (iter != mUpdateList.end())
		mUpdateList.erase(iter);

	gameObject->Terminate();

	mGameObjectFactory->Destroy(gameObject);
}

void Vishv::GameWorld::ProcessDestroyList()
{
	for (auto go : mDestroyList)
		DestroyInternal(go);
	mDestroyList.clear();
}

