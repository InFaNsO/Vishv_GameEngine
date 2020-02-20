#ifndef INCLUDED_VISHV_PHYSICS_AABB_H
#define INCLUDED_VISHV_PHYSICS_AABB_H

namespace Vishv::Physics::Collision
{
	class Collider;

	class AABB
	{
	public:
		void UpdatePosition(const Math::Vector3& v){ box.mTransform.mPosition = v;}

		void SetLengthX(float length) { box.SetLengthX(length); }
		void SetLengthY(float length) { box.SetLengthY(length); }
		void SetLengthZ(float length) { box.SetLengthZ(length); }

		void SetAAABB(const Vishv::Math::Shapes::Cuboid& cuboid)
		{
			box.mTransform.mPosition = cuboid.mTransform.mPosition;
			box.SetLengthX(cuboid.GetLengthX());
			box.SetLengthY(cuboid.GetLengthY());
			box.SetLengthZ(cuboid.GetLengthZ());
		}

		const Vishv::Math::Vector3& GetPosition() { return box.mTransform.mPosition; }
		float GetLengthX() { return box.GetLengthX(); }
		float GetLengthY() { return box.GetLengthY(); }
		float GetLengthZ() { return box.GetLengthZ(); }

		float GetMinX() { return box.mTransform.mPosition.x - box.GetLengthX() * 0.5f; }
		float GetMaxX() { return box.mTransform.mPosition.x - box.GetLengthX() * 0.5f; }
		float GetMinY() { return box.mTransform.mPosition.y - box.GetLengthY() * 0.5f; }
		float GetMaxY() { return box.mTransform.mPosition.y - box.GetLengthY() * 0.5f; }
		float GetMinZ() { return box.mTransform.mPosition.z - box.GetLengthZ() * 0.5f; }
		float GetMaxZ() { return box.mTransform.mPosition.z - box.GetLengthZ() * 0.5f; }


	private:
		friend class Collider;
		Vishv::Math::Shapes::Cuboid box;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_AABB_H


