#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_COLLIDER_H
#define INCLUDED_VISHV_PHYSICS_COLLIDER_H


namespace Vishv::Physics
{
	class RigidBody;

	class Collider
	{
	public:
		META_CLASS_DECLARE

		struct MinMax
		{
			Math::Vector3 min;
			Math::Vector3 max;
		};

		virtual MinMax GetBounds() = 0;
		virtual Math::Vector3 ClosestPointFrom(const Math::Vector3& pos) = 0;
		virtual Math::Vector3 ClosestPointOnBoundsFrom(const Math::Vector3& pos) = 0;

		bool IsTrigger();
		Math::Transform* myTransform = nullptr;

	protected:
		bool mIsTrigger = false;
		bool mIsActive = false;

		RigidBody* myRigidBody = nullptr;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_COLLIDER_H


