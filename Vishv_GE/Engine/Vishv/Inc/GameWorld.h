#ifndef INCLUDED_VISHV_GAME_WORLD
#define INCLUDED_VISHV_GAME_WORLD

#include "GameObjectFactory.h"
#include "Service.h"

namespace Vishv::Components
{
	class AIAgent;
	class ColliderComponent;
}

namespace Vishv
{
	class Editor;
	class GameObject;

	class GameWorld
	{
	public:
		void Register(GameObject& gameObject, bool isPlayer = false);
		void Register(Graphics::Camera& camera);

		GameObject* GetGameObject(std::string& name);
		GameObject* GetGameObject(int index) { return mGameObjects[index]; }

		std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }
		const std::vector<GameObject*>& GetGameObjects() const { return mGameObjects; }

		Graphics::Camera* GetMainCamera() { return mMainCamera; }

		AI::World<Components::AIAgent>& GetAIWorld();
		Physics::PhysicsWorld& GetPhysicsWorld();


		GameObject* Player() { return mPlayer; }
		GameObject* PathFinding() { return mPathFinding; }

	private:
		void Register(Components::AIAgent& agent, bool isPlayer = false);
		void Register(Physics::Collision::AABB& aabb);
		void Register(Components::ColliderComponent& cc);


		std::vector<GameObject*> mGameObjects;
		
		GameObject* mPlayer;
		GameObject* mPathFinding;

		std::vector<Graphics::Camera*> mGameCameras;
		Vishv::Graphics::Camera* mMainCamera;

		AI::World<Components::AIAgent> mAiWorld;
		Physics::PhysicsWorld mPhysicsWorld;

	public:
		void Initialize(size_t capacity);
		void Terminate();
		void Update(float deltaTime);
		void DebugUI();
		void Render();
		void SimpleDraw();

		GameObjectHandle Create(const std::filesystem::path& templateFileName, std::string name);
		GameObjectHandle Find(const std::string& name);
		void Destroy(GameObjectHandle handle);

		template<class T, class = std::void_t<std::is_base_of<Components::Component, T>>>
		T* AddService()
		{
			VISHVASSERT(!mIsInitialized, "[GameWorld] Cannot add services after being initialized");
			auto& newService = mServices.emplace_back(std::make_unique<T>());
			newService->mWorld = this;
			return static_cast<T*>(newService.get());
		}

		template <class T>
		const T* GetService() const
		{
			for (auto& service : mServices)
				if (service->GetMetaClass() == T::StaticGetMetaClass())
					return static_cast<T*>(service.get());
			return nullptr;
		}

		template <class T>
		T* GetService()
		{
			const GameWorld* constMe = this;
			return const_cast<T*>(constMe->GetService<T>());
		}

	private:
		friend class Editor;

		void DestroyInternal(GameObject* gameObject);
		void ProcessDestroyList();


		using GameObjectList = std::vector<GameObject*>;

		std::unique_ptr<Vishv::GameObjectFactory> mGameObjectFactory;
		std::unique_ptr<Vishv::GameObjectHandlePool> mGameObjectHandlePool;
		std::unique_ptr<Vishv::GameObjectAllocator> mGameObjectAllocator;

		using Services = std::vector<std::unique_ptr<Vishv::Service>>;
		Services mServices;

		GameObjectList mUpdateList;
		GameObjectList mDestroyList;

		bool mIsInitialized = false;
		bool mIsUpdating = false;
	};
}


#endif // !INCLUDED_VISHV_GAME_WORLD


