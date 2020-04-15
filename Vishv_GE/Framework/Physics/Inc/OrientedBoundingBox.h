#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_ORIENTEDBOUNDINGBOX_H
#define INCLUDED_VISHV_PHYSICS_ORIENTEDBOUNDINGBOX_H

#include "Collider.h"

namespace Vishv::Physics
{
	class SphereCollider;
	class CapsuleCollider;

	class OBB : public Collider
	{
	public:
		META_CLASS_DECLARE

		//Constructors
		OBB() = default;

	public:
		//Overrides
		MinMax GetBounds() override;
		Math::Vector3 ClosestPointFrom(const Math::Vector3 & pos) override;
		Math::Vector3 ClosestPointOnBoundsFrom(const Math::Vector3 & pos) override;
		CollisionData CheckCollision(Collider& other) const override;

	public:
		//Functions
		std::vector<Math::Vector3>& Points();


	private:
		friend class SphereCollider;
		friend class CapsuleCollider;

		
		CollisionData CollisionCheckCapsule(CapsuleCollider& other) const;
		CollisionData CollisionCheckSphere(SphereCollider& other) const;
		CollisionData CollisionCheckOBB(OBB& other) const;

		Math::Quaternion mOrientation;
		Math::Vector3 mExtent;

		std::vector<Math::Vector3> mPoints;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_ORIENTEDBOUNDINGBOX_H


