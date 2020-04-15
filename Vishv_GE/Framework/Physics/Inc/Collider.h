#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_COLLIDER_H
#define INCLUDED_VISHV_PHYSICS_COLLIDER_H


namespace Vishv::Physics
{
	class RigidBody;
	struct CollisionData;

	class Collider
	{
	public:
		META_CLASS_DECLARE

		struct MinMax
		{
			Math::Vector3 min;
			Math::Vector3 max;
		};

		virtual MinMax GetBounds() { return { Math::Vector3(-1.0f),  Math::Vector3(-1.0f) }; };
		virtual Math::Vector3 ClosestPointFrom(const Math::Vector3& pos) { return Math::Vector3(-1.0f); };
		virtual Math::Vector3 ClosestPointOnBoundsFrom(const Math::Vector3& pos) { return Math::Vector3(-1.0f); };
		virtual CollisionData CheckCollision(Collider& other) const;

		bool IsTrigger();
		RigidBody* myRigidBody = nullptr;

		Math::Transform* myTransform = nullptr;

	protected:
		friend class Collider;

		bool mIsTrigger = false;
		bool mIsActive = false;

	};
}

#endif // !INCLUDED_VISHV_PHYSICS_COLLIDER_H


