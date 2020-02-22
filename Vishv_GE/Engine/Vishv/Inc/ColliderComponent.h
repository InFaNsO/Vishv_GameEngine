#ifndef INCLUDED_VISHV_COLLIDER_COMPONENT
#define INCLUDED_VISHV_COLLIDER_COMPONENT

#include "Component.h"

namespace Vishv
{
	class GameWorld;
	class GameObject;
}

namespace Vishv::Components
{
	class TransformComponent;

	class ColliderComponent : public Component
	{
	public:
		META_CLASS_DECLARE;
		void Initialize()override;
		void Update(float deltaTime) override;
		void DebugUI() override;
		void SimpleDraw() override;

		void SetTag(int tag);
		int GetTag();

		bool IsColliding(int tag);

		std::vector<GameObject*> GetCollisions(int tag);

		float GetRange() { return mSphereCollider.mSphere.mRadius; }

	private:
		friend class GameWorld;

		int mTag;

		TransformComponent* mTransformComponent;
		Vishv::Physics::SphereCollider mSphereCollider;
		Vishv::Math::Vector3 mOffset;

		Vishv::Physics::PhysicsWorld* pworld;
	};
}


#endif // !INCLUDED_VISHV_COLLIDER_COMPONENT


