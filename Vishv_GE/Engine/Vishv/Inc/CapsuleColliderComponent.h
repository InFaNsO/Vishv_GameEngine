#ifndef INCLUDED_VISHV_CAPSULE_COLLIDER_COMPONENT
#define INCLUDED_VISHV_CAPSULE_COLLIDER_COMPONENT

#include "Component.h"

namespace Vishv
{
	class GameWorld;
	class GameObject;
}

namespace Vishv::Components
{
	class TransformComponent;

	class CapsuleCollider : public Component
	{
	public:
		META_CLASS_DECLARE;

		void Initialize()override;
		void Update(float deltaTime) override;
		void DebugUI() override;
		void SimpleDraw() override;


		void SetTag(int tag) { mTag = tag; }
		int GetTag() { return mTag; }

		bool IsTrigger() { return mColliderCapsule.IsTrigger(); }
		bool IsStatic();

		//bool IsColliding(int tag);

		//std::vector<GameObject*> GetCollisions(int tag);

		//float GetRange() { return mSphereCollider.mSphere.mRadius; }

	private:
		bool firstUpdate = false;
		void DoFirstUpdate();


		int mTag;

		TransformComponent* mTransformComponent;
		Vishv::Physics::CapsuleCollider mColliderCapsule;
	};
}
#endif
