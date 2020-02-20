#include "Precompiled.h"
#include "ShapeCollision.h"

using namespace Vishv;
using namespace Vishv::Physics;
using namespace Vishv::Physics::Collision;

namespace
{
	Math::Vector3 GetPoint(AABB& firstBox, AABB& secondBox)
	{
		Math::Vector3 first = firstBox.GetPosition();
		Math::Vector3 second = secondBox.GetPosition();

		if (first.y > second.y)
		{
			if (first.x > second.x)
			{
				if (first.z > second.z)
				{
					return { first.x - firstBox.GetLengthX() * 0.5f, first.y - firstBox.GetLengthY() * 0.5f, first.z - firstBox.GetLengthZ() * 0.5f };
				}
				else
				{
					return { first.x - firstBox.GetLengthX() * 0.5f, first.y - firstBox.GetLengthY() * 0.5f, first.z + firstBox.GetLengthZ() * 0.5f };
				}
			}
			else
			{
				if (first.z > second.z)
				{
					return { first.x + firstBox.GetLengthX() * 0.5f, first.y - firstBox.GetLengthY() * 0.5f, first.z - firstBox.GetLengthZ() * 0.5f };
				}
				else
				{
					return { first.x + firstBox.GetLengthX() * 0.5f, first.y - firstBox.GetLengthY() * 0.5f, first.z - firstBox.GetLengthZ() * 0.5f };
				}
			}
		}
		else
		{
			if (first.x > second.x)
			{
				if (first.z > second.z)
				{
					return { first.x - firstBox.GetLengthX() * 0.5f, first.y + firstBox.GetLengthY() * 0.5f, first.z - firstBox.GetLengthZ() * 0.5f };
				}
				else
				{
					return { first.x - firstBox.GetLengthX() * 0.5f, first.y + firstBox.GetLengthY() * 0.5f, first.z + firstBox.GetLengthZ() * 0.5f };
				}
			}
			else
			{
				if (first.z > second.z)
				{
					return { first.x + firstBox.GetLengthX() * 0.5f, first.y + firstBox.GetLengthY() * 0.5f, first.z - firstBox.GetLengthZ() * 0.5f };
				}
				else
				{
					return { first.x + firstBox.GetLengthX() * 0.5f, first.y + firstBox.GetLengthY() * 0.5f, first.z + firstBox.GetLengthZ() * 0.5f };
				}
			}
		}
	}

	Math::Vector3 GetPoint(AABB& aabb, Math::Vector3& point)
	{
		Math::Vector3 boxPos = aabb.GetPosition();
		if (boxPos.y > point.y)
		{
			if (boxPos.x > point.x)
			{
				if (boxPos.z > point.z)
				{
					return { boxPos.x - aabb.GetLengthX() * 0.5f, boxPos.y - aabb.GetLengthY() * 0.5f, boxPos.z - aabb.GetLengthZ() * 0.5f };
				}
				else
				{
					return { boxPos.x - aabb.GetLengthX() * 0.5f, boxPos.y - aabb.GetLengthY() * 0.5f, boxPos.z + aabb.GetLengthZ() * 0.5f };
				}
			}
			else
			{
				if (boxPos.z > point.z)
				{
					return { boxPos.x + aabb.GetLengthX() * 0.5f, boxPos.y - aabb.GetLengthY() * 0.5f, boxPos.z - aabb.GetLengthZ() * 0.5f };
				}
				else
				{
					return { boxPos.x + aabb.GetLengthX() * 0.5f, boxPos.y - aabb.GetLengthY() * 0.5f, boxPos.z - aabb.GetLengthZ() * 0.5f };
				}
			}
		}
		else
		{
			if (boxPos.x > point.x)
			{
				if (boxPos.z > point.z)
				{
					return { boxPos.x - aabb.GetLengthX() * 0.5f, boxPos.y + aabb.GetLengthY() * 0.5f, boxPos.z - aabb.GetLengthZ() * 0.5f };
				}
				else
				{
					return { boxPos.x - aabb.GetLengthX() * 0.5f, boxPos.y + aabb.GetLengthY() * 0.5f, boxPos.z + aabb.GetLengthZ() * 0.5f };
				}
			}
			else
			{
				if (boxPos.z > point.z)
				{
					return { boxPos.x + aabb.GetLengthX() * 0.5f, boxPos.y + aabb.GetLengthY() * 0.5f, boxPos.z - aabb.GetLengthZ() * 0.5f };
				}
				else
				{
					return { boxPos.x + aabb.GetLengthX() * 0.5f, boxPos.y + aabb.GetLengthY() * 0.5f, boxPos.z + aabb.GetLengthZ() * 0.5f };
				}
			}
		}
	}

}

CollisionData Collider::IsColliding(Math::Shapes::Sphere & sphere, Math::Shapes::Sphere & sphere2)
{
	CollisionData data;
	data.Shape1 = &sphere;
	data.Shape2 = &sphere2;

	if(!IsCollision(sphere, sphere2))
		return data;

	//they are colliding
	data.Collided = true;
	
	Vishv::Math::Vector3 dir = sphere2.mTransform.mPosition - sphere.mTransform.mPosition;
	dir.Normalize();
	
	data.PointOfCollisionShape1 = sphere.mTransform.mPosition + (dir * sphere.mRadius);
	data.PointOfCollisionShape2 = sphere2.mTransform.mPosition + (-dir * sphere2.mRadius);

	return data;
}

CollisionData Vishv::Physics::Collision::Collider::IsColliding(AABB & aabb, AABB & aabb2)
{
	CollisionData data;
	data.Shape1 = &aabb.box;
	data.Shape2 = &aabb2.box;

	if (IsCollision(aabb, aabb2))
	{
		data.Collided = true;
		data.distanceSqr = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(aabb.box.mTransform.mPosition - aabb2.box.mTransform.mPosition));

		data.PointOfCollisionShape1 = GetPoint(aabb, aabb2);
		data.PointOfCollisionShape2 = GetPoint(aabb2, aabb);
	}

	return data;
}

CollisionData Vishv::Physics::Collision::Collider::IsColliding(Math::Shapes::Sphere & sphere, AABB & aabb)
{
	CollisionData data;
	data.Shape1 = &sphere;
	data.Shape2 = &aabb.box;

	Math::Vector3 direction = aabb.GetPosition() - sphere.mTransform.mPosition;
	direction.Normalize();

	data.PointOfCollisionShape1 = sphere.mTransform.mPosition + (direction * sphere.mRadius);

	if (IsCollision(sphere, aabb))
	{
		data.Collided = true;
		data.distanceSqr = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(aabb.box.mTransform.mPosition - sphere.mTransform.mPosition));

		data.PointOfCollisionShape2 = GetPoint(aabb, data.PointOfCollisionShape1);
	}

	return data;
}


bool Vishv::Physics::Collision::Collider::IsCollision(Math::Shapes::Sphere & sphere, Math::Shapes::Sphere & sphere2)
{
	float distanceSqr = Math::Abs(Math::MagnitudeSqr(sphere.mTransform.mPosition - sphere2.mTransform.mPosition));
	if (Math::Abs(Math::MagnitudeSqr(sphere.mTransform.mPosition - sphere2.mTransform.mPosition)) > sphere.mRadius * sphere.mRadius + sphere2.mRadius * sphere2.mRadius)
		return false;
	return true;
}

bool Vishv::Physics::Collision::Collider::IsCollision(Math::Shapes::Sphere & sphere, AABB & aabb)
{
	Math::Vector3 point = sphere.mTransform.mPosition + (Math::Normalize(aabb.GetPosition() - sphere.mTransform.mPosition) * sphere.mRadius);

	if (aabb.GetMinX() <= point.x && aabb.GetMaxX() >= point.x)
		if (aabb.GetMinY() <= point.y && aabb.GetMaxY() >= point.y)
			if (aabb.GetMinZ() <= point.z && aabb.GetMaxZ() >= point.z)
				return true;
	return false;
}

bool Vishv::Physics::Collision::Collider::IsCollision(AABB & aabb, AABB & aabb2)
{
	if (aabb.GetMinX() <= aabb2.GetMaxX() && aabb.GetMaxX() >= aabb2.GetMinX())
		if (aabb.GetMinY() <= aabb2.GetMaxY() && aabb.GetMaxY() >= aabb2.GetMinY())
			if (aabb.GetMinZ() <= aabb2.GetMaxZ() && aabb.GetMaxZ() >= aabb2.GetMinZ())
				return true;

	return false;
}


