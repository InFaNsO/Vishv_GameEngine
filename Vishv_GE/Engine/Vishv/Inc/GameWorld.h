#ifndef INCLUDED_VISHV_GAME_WORLD
#define INCLUDED_VISHV_GAME_WORLD

#include "GameObjectFactory.h"
#include "Service.h"

namespace Vishv
{
	class EditorManager;
	class GameObject;
	class PostProcessService;

	class GameWorld
	{
	public:
		void Initialize(size_t capacity);
		void Terminate();
		void Update();
		void DebugUI();
		void Render();
		void SimpleDraw();

		GameObjectHandle RegisterGameObject(GameObject&& object);
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

		template<class T, class = std::void_t<std::is_base_of<Components::Component, T>>>
		const T* GetService() const
		{
			for (auto& service : mServices)
				if (service->GetMetaClass() == T::StaticGetMetaClass())
					return static_cast<T*>(service.get());
			return nullptr;
		}

		template<class T, class = std::void_t<std::is_base_of<Components::Component, T>>>
		T* GetService()
		{
			const GameWorld* constMe = this;
			return const_cast<T*>(constMe->GetService<T>());
		}

		void LoadGameWorld(const std::filesystem::path& worldFileName);
		GameObjectHandle CreateNewGameObject();

	private:
		friend class EditorManager;
		PostProcessService* mRenderer = nullptr;

		GameObject* CreateGameObject();
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


