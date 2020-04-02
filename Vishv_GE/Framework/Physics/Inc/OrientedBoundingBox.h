#pragma once
#ifndef INCLUDED_VISHV_PHYSICS_ORIENTEDBOUNDINGBOX_H
#define INCLUDED_VISHV_PHYSICS_ORIENTEDBOUNDINGBOX_H

#include "Collider.h"

namespace Vishv::Physics
{
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

	public:
		//Functions
		std::vector<Math::Vector3>& Points();


	private:
		Math::Quaternion mOrientation;
		Math::Vector3 mExtent;

		std::vector<Math::Vector3> mPoints;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_ORIENTEDBOUNDINGBOX_H


