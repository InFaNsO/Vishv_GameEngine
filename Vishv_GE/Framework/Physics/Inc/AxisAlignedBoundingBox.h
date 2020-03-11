#ifndef INCLUDED_VISHV_PHYSICS_AABB_H
#define INCLUDED_VISHV_PHYSICS_AABB_H

namespace Vishv::Physics::Collision
{
	class Collider;

	class AABB
	{
	public:
		AABB() = default;

		AABB(const Math::Vector3& min, const Math::Vector3& max, const Math::Vector3& center)
		{
			box.mTransform.mPosition = center;
			box.SetLengthX(min.x - max.x);
			box.SetLengthY(min.y - max.y);
			box.SetLengthZ(min.z - max.z);
		}

		AABB(const Math::Vector3& center, const Math::Vector3& extend)
		{
			box.mTransform.mPosition = center;
			box.SetLengthX(extend.x);
			box.SetLengthY(extend.y);
			box.SetLengthZ(extend.z);
		}
		AABB(const Math::Vector3& extend)
		{
			box.SetLengthX(extend.x);
			box.SetLengthY(extend.y);
			box.SetLengthZ(extend.z);
		}
		static AABB FromMinMax(const Math::Vector3& min, const Math::Vector3& max)
		{
			AABB a;

			a.SetLengthX(max.x - min.x);
			a.SetLengthY(max.y - min.y);
			a.SetLengthZ(max.z - min.z);

			return a;
		}

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
		float GetLengthX() const { return box.GetLengthX(); }
		float GetLengthY() const { return box.GetLengthY(); }
		float GetLengthZ() const { return box.GetLengthZ(); }

		float GetMinX() const { return box.mTransform.mPosition.x - box.GetLengthX() * 0.5f; }
		float GetMaxX() const { return box.mTransform.mPosition.x - box.GetLengthX() * 0.5f; }
		float GetMinY() const { return box.mTransform.mPosition.y - box.GetLengthY() * 0.5f; }
		float GetMaxY() const { return box.mTransform.mPosition.y - box.GetLengthY() * 0.5f; }
		float GetMinZ() const { return box.mTransform.mPosition.z - box.GetLengthZ() * 0.5f; }
		float GetMaxZ() const { return box.mTransform.mPosition.z - box.GetLengthZ() * 0.5f; }

		Math::Vector3 Extent()
		{
			return Math::Vector3(GetMaxX() - GetMinX(), GetMaxY() - GetMinY(), GetMaxZ() - GetMinZ());
		}

		static AABB Generate(const Vishv::Graphics::Mesh& mesh)
		{
			VISHVASSERT(mesh.mVertices.size() != 0, "Mesh is empty");

			Math::Vector3 min = mesh.mVertices[0].position;
			Math::Vector3 max = mesh.mVertices[0].position;

			for (auto& vertex : mesh.mVertices)
			{
				min.x = min.x < vertex.position.x ? min.x : vertex.position.x;
				min.y = min.y < vertex.position.y ? min.y : vertex.position.y;
				min.z = min.z < vertex.position.z ? min.z : vertex.position.z;

				max.x = max.x < vertex.position.x ? max.x : vertex.position.x;
				max.y = max.y < vertex.position.y ? max.y : vertex.position.y;
				max.z = max.z < vertex.position.z ? max.z : vertex.position.z;
			}

			return AABB(min, max, {});
		}
	private:
		friend class Collider;
		Vishv::Math::Shapes::Cuboid box;
	};
}

#endif // !INCLUDED_VISHV_PHYSICS_AABB_H


