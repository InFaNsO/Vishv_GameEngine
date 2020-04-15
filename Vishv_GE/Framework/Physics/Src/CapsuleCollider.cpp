#include "Precompiled.h"
#include "CapsuleCollider.h"

#include "CollisionData.h"
#include "RigidBody.h"

#include "AxisAlignedBoundingBox.h"
#include "OrientedBoundingBox.h"
#include "SphereCollider.h"

using namespace Vishv;
using namespace Physics;

META_DERIVED_BEGIN(CapsuleCollider, Collider)
	META_FIELD_BEGIN
		META_FIELD(mRadius, "Raddius")
		META_FIELD(mHeight, "Height")
	META_FIELD_END
META_CLASS_END



Collider::MinMax Vishv::Physics::CapsuleCollider::GetBounds()
{
	return Collider::MinMax();
	//return { { myTransform->Position() - mRadius }, {myTransform->Position() + mRadius} };
}

Math::Vector3 Vishv::Physics::CapsuleCollider::ClosestPointFrom(const Math::Vector3& pos)
{
	return Math::Vector3();

//	auto dir = (pos - myTransform->Position()).Normalized();
//	return myTransform->Position() + (dir * mRadius);
}

Math::Vector3 Vishv::Physics::CapsuleCollider::ClosestPointOnBoundsFrom(const Math::Vector3& pos)
{
	return Math::Vector3();
	//auto dir = (pos - myTransform->Position()).Normalized();
	//return myTransform->Position() + (dir * AABB::FromMinMax(myTransform->Position() - mRadius, myTransform->Position() + mRadius).Extent());
}


CollisionData Vishv::Physics::CapsuleCollider::CheckCollision(Collider& other) const
{
	if (other.GetMetaClass()->GetName() == SphereCollider::StaticGetMetaClass()->GetName())
		return std::move(CollisionCkeckSphere(*static_cast<SphereCollider*>(&other)));
	else if (other.GetMetaClass()->GetName() == OBB::StaticGetMetaClass()->GetName())
		return std::move(CollisionCkeckOBB(*static_cast<OBB*>(&other)));
	else if (other.GetMetaClass()->GetName() == CapsuleCollider::StaticGetMetaClass()->GetName())
		return std::move(CollisionCheckCapsule(*static_cast<CapsuleCollider*>(&other)));


	return std::move(CollisionData());
}

CollisionData Vishv::Physics::CapsuleCollider::CollisionCheckCapsule(CapsuleCollider& other) const
{
	CollisionData cData;
	return std::move(cData);
}

CollisionData Vishv::Physics::CapsuleCollider::CollisionCkeckSphere(SphereCollider& other) const
{
	CollisionData cData;
	//	float distanceSq = Math::Abs(Math::MagnitudeSqr(myTransform->Position() - other.myTransform->Position())) - ((mRadius * mRadius) + (other.mRadius * other.mRadius));
//
//	//Sphere sphere check
//	if (distanceSq > 0.0f)
//	{
//		cData.IsColliding = false;
//		return std::move(cData);
//	}
//
//	cData.distanceInsertion = sqrtf(Math::Abs(distanceSq));
//	cData.other = other.myRigidBody;
	return std::move(cData);
}

CollisionData Vishv::Physics::CapsuleCollider::CollisionCkeckOBB(OBB& other) const
{
	CollisionData cData;

//	//Find extent after orientation 
//	//multiply with unit vector of direction to sphere == "Radius"
//
//	float radiusSq = Math::Abs(((other.mExtent * other.mOrientation) * (myTransform->Position() - other.myTransform->Position()).Normalized()).MagnitudeSq());
//	float distanceSq = Math::Abs(Math::MagnitudeSqr(myTransform->Position() - other.myTransform->Position())) - ((mRadius * mRadius) + (radiusSq));
//
//	if (distanceSq > 0.0f)
//	{
//		cData.IsColliding = false;
//		return std::move(cData);
//	}
//
//	cData.distanceInsertion = sqrtf(Math::Abs(distanceSq));
//	cData.other = other.myRigidBody;

	return std::move(cData);
}

