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

	EditorManager::Get()->mWorld = this;
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

void Vishv::GameWorld::Update()
{
	if (!mIsInitialized)
		return;

	VISHVASSERT(!mIsUpdating, "Already Updateing");

	for (auto& service : mServices)
		service->Update();

	mIsUpdating = true;

	for (size_t i = 0; i < mUpdateList.size(); ++i)
	{
		auto go = mUpdateList[i];
		if (go->mHandle.IsValid())
			go->Update();
	}

	mIsUpdating = false;

	ProcessDestroyList();
}

void Vishv::GameWorld::SimpleDraw()
{
	if (!mIsInitialized)
		return;
	for (auto gameObject : mUpdateList)
		gameObject->SimpleDraw();
}

void Vishv::GameWorld::DebugUI()
{
	/*if (!mIsInitialized)
		return;
	ImGui::Begin("Heirarchy");
	static Service* selectedService = nullptr;
	static GameObject* selectedObject = nullptr;
	if (ImGui::CollapsingHeader("Services"))
	{
		for (auto& service : mServices)
		{
			if (ImGui::Button(service.get()->GetTypeID().c_str()))
			{
				selectedObject = nullptr;
				selectedService = service.get();
			}
		}
	}
	if (ImGui::CollapsingHeader("Game Objects"))
	{
		for (auto& go : mUpdateList)
		{
			if (ImGui::Button(go->mName.c_str()))
			{
				selectedService = nullptr;
				selectedObject = go;
			}
		}
	}

	if (ImGui::Button("Add Game Object"))
	{
		selectedObject = CreateGameObject();
		selectedService = nullptr;
	}
	
	ImGui::End();

	ImGui::Begin("Inspector");

	if (selectedService)
	{
		selectedService->DoUI(selectedService, *selectedService->GetMetaClass());
		selectedService->DebugUI();
	}
	else if (selectedObject)
	{
		//do meta ui then custom ui
		selectedObject->DebugUI();
	}

	ImGui::End();*/
}

void Vishv::GameWorld::Render()
{
	if (!mIsInitialized)
		return;

	auto editor = Vishv::EditorManager::Get();

	editor->mSceneRender.mRenderTarget.BeginRender();

	for (auto& service : mServices)
		service->Render();

	for (auto gameObject : mUpdateList)
		gameObject->Render();

	editor->mSceneRender.mRenderTarget.EndRender();
}


GameObjectHandle Vishv::GameWorld::RegisterGameObject(GameObject&& object)
{
	auto pointer = mGameObjectFactory->Add(std::move(object));
	GameObjectHandle handle = mGameObjectHandlePool->Register(pointer);
	pointer->mWorld = this;
	pointer->mHandle = handle;
	pointer->Initialize();

	mUpdateList.push_back(pointer);
	return handle;
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

void Vishv::GameWorld::LoadGameWorld(const std::filesystem::path& worldFileName)
{
	//get all the objects / object file names and load them 
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

GameObject* Vishv::GameWorld::CreateGameObject()
{
	auto go = mGameObjectFactory->CreateEmpty();
	go->mWorld = this;
	go->mHandle = mGameObjectHandlePool->Register(go);
	mUpdateList.push_back(go);
	return go;
}
