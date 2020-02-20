#ifndef INCLUDED_VISHV_GAME_WORLD
#define INCLUDED_VISHV_GAME_WORLD

#include "GameObjectFactory.h"

namespace Vishv::Components
{
	class AIAgent;
	class ColliderComponent;
}

namespace Vishv
{
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

	private:
		void DestroyInternal(GameObject* gameObject);
		void ProcessDestroyList();


		using GameObjectList = std::vector<GameObject*>;

		std::unique_ptr<Vishv::GameObjectFactory> mGameObjectFactory;
		std::unique_ptr<Vishv::GameObjectHandlePool> mGameObjectHandlePool;
		std::unique_ptr<Vishv::GameObjectAllocator> mGameObjectAllocator;

		GameObjectList mUpdateList;
		GameObjectList mDestroyList;

		bool mIsInitialized = false;
		bool mIsUpdating = false;
	};
}


#endif // !INCLUDED_VISHV_GAME_WORLD


