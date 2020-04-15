#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_CAPSULECOLLIDER_H
#define INCLUDED_VISHV_PHYSICS_CAPSULECOLLIDER_H

#include "Collider.h"

namespace Vishv::Physics
{
	class OBB;
	class SphereCollider;

	class CapsuleCollider : public Collider
	{
	public:
		META_CLASS_DECLARE

		//Constructors
		CapsuleCollider() = default;



	public:
		//Overrides
		MinMax GetBounds() override;
		Math::Vector3 ClosestPointFrom(const Math::Vector3& pos) override;
		Math::Vector3 ClosestPointOnBoundsFrom(const Math::Vector3& pos) override;
		CollisionData CheckCollision(Collider& other) const override;

	public:
		//Functions
		float Radius() { return mRadius; }
		const float Radius() const { return mRadius; }

		float Height() { return mHeight; }
		const float Height() const { return mHeight; }

	private:
		friend class OBB;

		CollisionData CollisionCheckCapsule(CapsuleCollider& other) const;
		CollisionData CollisionCkeckSphere(SphereCollider& other) const;
		CollisionData CollisionCkeckOBB(OBB& other) const;


		float mRadius;
		float mHeight;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_SPHERECOLLIDER_H


