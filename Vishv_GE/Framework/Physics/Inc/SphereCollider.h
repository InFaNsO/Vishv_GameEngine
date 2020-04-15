#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_SPHERECOLLIDER_H
#define INCLUDED_VISHV_PHYSICS_SPHERECOLLIDER_H

#include "Collider.h"

namespace Vishv::Physics
{
	class OBB;

	class SphereCollider : public Collider
	{
	public:
		META_CLASS_DECLARE

		//Constructors
		SphereCollider() = default;
		SphereCollider(float radius)
			:mRadius(radius)
		{}


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

	private:
		friend class OBB;

		CollisionData CollisionCkeckSphere(SphereCollider& other) const;
		CollisionData CollisionCkeckOBB(OBB& other) const;

		float mRadius;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_SPHERECOLLIDER_H


