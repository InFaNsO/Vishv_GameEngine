#include "Precompiled.h"
#include "RayCast.h"
#include "ShapeCollision.h"
#include "AxisAlignedBoundingBox.h"

namespace
{
	bool IsPointOnRay(Vishv::Physics::Ray& ray, Vishv::Math::Vector3& point)
	{
		Vishv::Math::Vector3 v = point - ray.origin;
		Vishv::Math::Vector3 cross = Vishv::Math::Cross(ray.direction, v);

		float dis = Vishv::Math::Magnitude(cross) / Vishv::Math::Magnitude(ray.direction);

		if (dis < 0.1f)
			return true;

		return false;
	}
}

bool Vishv::Physics::Raycast::IsColliding(Ray & ray, float length, Math::Shapes::Cuboid & cuboid, Math::Vector3& collisionPoint)
{
	//do a distance check
	Math::Shapes::Sphere rayS;
	rayS.mRadius = length;
	rayS.mTransform.mPosition = ray.origin;
	Collision::AABB aabb;
	aabb.SetAAABB(cuboid);

	auto coll = Collision::Collider::IsColliding(rayS, aabb);

	if (!coll.Collided)
		return false;

	if (IsPointOnRay(ray, coll.PointOfCollisionShape2))
	{
		collisionPoint = coll.PointOfCollisionShape2;
		return true;
	}
	return false;
}

bool Vishv::Physics::Raycast::IsColliding(Ray & ray, float length, Math::Shapes::Sphere & sphere, Math::Vector3& collisionPoint)
{
	//do a distance check
	Math::Shapes::Sphere rayS;
	rayS.mRadius = length;
	rayS.mTransform.mPosition = ray.origin;
	auto coll = Collision::Collider::IsColliding(rayS, sphere);

	if (!coll.Collided)
		return false;

	if (IsPointOnRay(ray, coll.PointOfCollisionShape2))
	{
		collisionPoint = coll.PointOfCollisionShape2;
		return true;
	}
	return false;
}
