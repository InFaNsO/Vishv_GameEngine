#ifndef INCLUDED_VISHV_PHYSICS_AABB_H
#define INCLUDED_VISHV_PHYSICS_AABB_H

#include "Collider.h"

namespace Vishv::Physics
{
	class AABB : public Collider
	{
	public:
		META_CLASS_DECLARE

		//Constructors
		AABB() = default;
		AABB(const Math::Vector3& min, const Math::Vector3& max, const Math::Vector3& center);
		AABB(const Math::Vector3& center, const Math::Vector3& extend);
		AABB(const Math::Vector3& extend);

	public:
		//Statics
		static AABB Generate(const Vishv::Graphics::Mesh& mesh);
		static AABB FromMinMax(const Math::Vector3& min, const Math::Vector3& max);

	public:
		//Overrides
		MinMax GetBounds() override;
		Math::Vector3 ClosestPointFrom(const Math::Vector3& pos) override;
		Math::Vector3 ClosestPointOnBoundsFrom(const Math::Vector3& pos) override;

	public:

		void SetAAABB(const Vishv::Math::Shapes::Cuboid& cuboid);

		float GetLengthX() const { return max.x - min.x; }
		float GetLengthY() const { return max.y - min.y; }
		float GetLengthZ() const { return max.z - min.z; }

		float GetMinX() const { return myTransform->Position().x - GetLengthX() * 0.5f; }
		float GetMaxX() const { return myTransform->Position().x - GetLengthX() * 0.5f; }
		float GetMinY() const { return myTransform->Position().y - GetLengthY() * 0.5f; }
		float GetMaxY() const { return myTransform->Position().y - GetLengthY() * 0.5f; }
		float GetMinZ() const { return myTransform->Position().z - GetLengthZ() * 0.5f; }
		float GetMaxZ() const { return myTransform->Position().z - GetLengthZ() * 0.5f; }

		Math::Vector3 Extent()
		{
			return Math::Vector3(GetMaxX() - GetMinX(), GetMaxY() - GetMinY(), GetMaxZ() - GetMinZ());
		}

		bool IsPointInside(const Math::Vector3& pos);

	public:
		Math::Vector3 min;
		Math::Vector3 max;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_AABB_H


