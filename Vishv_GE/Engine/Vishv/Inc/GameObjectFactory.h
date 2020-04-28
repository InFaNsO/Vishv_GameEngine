#ifndef INCLUDED_VISHV_GAME_OBJECT_FACTORY_H
#define INCLUDED_VISHV_GAME_OBJECT_FACTORY_H

#include "GameObject.h"

namespace Vishv
{
	class GameObjectFactory
	{
	public:
		GameObjectFactory(GameObjectAllocator& allocator);
		GameObject* Add(GameObject&& gameObj);
		GameObject* Create(const std::filesystem::path& templateFileName);
		GameObject* CreateEmpty();
		void Destroy(GameObject* gameObject);
	private:
		GameObjectAllocator& mGameObjectAllocator;
	};
}

#endif // !INCLUDED_VISHV_GAME_OBJECT_FACTORY_H


