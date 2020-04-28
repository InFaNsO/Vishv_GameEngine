#ifndef INCLUDED_VISHV_GAME_OBJECT_H
#define INCLUDED_VISHV_GAME_OBJECT_H

namespace Vishv::Components
{
	class Component;
}
namespace Vishv
{
	class Editor;
	class GameWorld;
	class GameObject;

	using GameObjectAllocator = Core::TypedAllocator<GameObject>;
	using GameObjectHandle = Core::Handle<GameObject>;
	using GameObjectHandlePool = Core::HandlePool<GameObject>;

	class GameObject	final
	{
	public:
		META_CLASS_DECLARE

		GameObject() = default;

		void Initialize();
		void Terminate();
		
		void Update();
		void Render();
		void DebugUI();
		void SimpleDraw();


		Components::Component* AddComponent(const Core::Meta::MetaClass& metaClass);

		template<class T, class = std::void_t<std::is_base_of<Components::Component, T>>>
		T* AddComponent()
		{
			auto& newComponent = mComponents.emplace_back(std::make_unique<T>());
			newComponent->mOwner = this;
			return static_cast<T*>(newComponent.get());
		}

		template <class T, class = std::void_t<std::is_base_of<Components::Component, T>>>
		const T* GetComponent() const
		{
			for (auto& component : mComponents)
				if (component->GetMetaClass() == T::StaticGetMetaClass())
					return static_cast<T*>(component.get());
			return nullptr;
		}

		template <class T, class = std::void_t<std::is_base_of<Components::Component, T>>>
		T* GetComponent()
		{
			const GameObject* constMe = this;
			return const_cast<T*>(constMe->GetComponent<T>());
		}

		GameWorld& GetWorld() { return *mWorld; }
		const GameWorld& GetWorld() const { return *mWorld; }

		void SetName(const char* name) { mName = name; }
		const char* GetName() { return mName.c_str(); }
		GameObjectHandle GetHandle() { return mHandle; }

		bool IsActive() const { return mIsActive; }
		void SetActive(bool set) { mIsActive = set; }

	private:
		friend class GameWorld;
		friend class Editor;

		GameWorld* mWorld = nullptr;
		GameObjectHandle mHandle;

		Vishv::AI::Graph g;

		bool mIsActive = true;

		char componentName[256] = "";

		std::vector<std::unique_ptr<Components::Component>> mComponents;
		std::string mName = "NoName";
	};
}


#endif // !INCLUDED_VISHV_GAME_OBJECT_H


