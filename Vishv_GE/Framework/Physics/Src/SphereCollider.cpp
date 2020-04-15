#include "Precompiled.h"
#include "SphereCollider.h"

#include "CollisionData.h"
#include "RigidBody.h"

#include "AxisAlignedBoundingBox.h"
#include "OrientedBoundingBox.h"

using namespace Vishv;
using namespace Physics;

META_DERIVED_BEGIN(SphereCollider, Collider)
	META_FIELD_BEGIN
		META_FIELD(mRadius, "Raddius")
	META_FIELD_END
META_CLASS_END

Collider::MinMax Vishv::Physics::SphereCollider::GetBounds()
{
	return { { myTransform->Position() - mRadius }, {myTransform->Position() + mRadius} };
}

Math::Vector3 Vishv::Physics::SphereCollider::ClosestPointFrom(const Math::Vector3& pos)
{
	auto dir = (pos - myTransform->Position()).Normalized();
	return myTransform->Position() + (dir * mRadius);
}

Math::Vector3 Vishv::Physics::SphereCollider::ClosestPointOnBoundsFrom(const Math::Vector3& pos)
{
	auto dir = (pos - myTransform->Position()).Normalized();
	return myTransform->Position() + (dir * AABB::FromMinMax(myTransform->Position() - mRadius, myTransform->Position() + mRadius).Extent());
}


CollisionData Vishv::Physics::SphereCollider::CheckCollision(Collider& other) const
{
	if (other.GetMetaClass()->GetName() == SphereCollider::StaticGetMetaClass()->GetName())
		return std::move(CollisionCkeckSphere(*static_cast<SphereCollider*>(&other)));
	else if (other.GetMetaClass()->GetName() == OBB::StaticGetMetaClass()->GetName())
		return std::move(CollisionCkeckOBB(*static_cast<OBB*>(&other)));

	return std::move(CollisionData());
}

CollisionData Vishv::Physics::SphereCollider::CollisionCkeckSphere(SphereCollider& other) const
{
	CollisionData cData;
	float distanceSq = Math::Abs(Math::MagnitudeSqr(myTransform->Position() - other.myTransform->Position())) - ((mRadius * mRadius) + (other.mRadius * other.mRadius));

	//Sphere sphere check
	if (distanceSq > 0.0f)
	{
		cData.IsColliding = false;
		return std::move(cData);
	}

	cData.distanceInsertion = sqrtf(Math::Abs(distanceSq));
	cData.other = other.myRigidBody;
	return std::move(cData);
}

CollisionData Vishv::Physics::SphereCollider::CollisionCkeckOBB(OBB& other) const
{
	CollisionData cData;

	//Find extent after orientation 
	//multiply with unit vector of direction to sphere == "Radius"

	float radiusSq = Math::Abs(((other.mExtent * other.mOrientation) * (myTransform->Position() - other.myTransform->Position()).Normalized()).MagnitudeSq());
	float distanceSq = Math::Abs(Math::MagnitudeSqr(myTransform->Position() - other.myTransform->Position())) - ((mRadius * mRadius) + (radiusSq));

	if (distanceSq > 0.0f)
	{
		cData.IsColliding = false;
		return std::move(cData);
	}

	cData.distanceInsertion = sqrtf(Math::Abs(distanceSq));
	cData.other = other.myRigidBody;

	return std::move(cData);
}

