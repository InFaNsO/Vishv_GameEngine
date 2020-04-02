#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_SPHERECOLLIDER_H
#define INCLUDED_VISHV_PHYSICS_SPHERECOLLIDER_H

#include "Collider.h"

namespace Vishv::Physics
{
	class SphereCollider : public Collider
	{
	public:
		META_CLASS_DECLARE

		//Constructors
		SphereCollider() = default;
		SphereCollider(float radius);

	public:
		//Overrides
		MinMax GetBounds() override;
		Math::Vector3 ClosestPointFrom(const Math::Vector3& pos) override;
		Math::Vector3 ClosestPointOnBoundsFrom(const Math::Vector3& pos) override;

	public:
		//Functions
		float Radius() { return mRadius; }
		const float Radius() const { return mRadius; }

	private:
		float mRadius;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_SPHERECOLLIDER_H


