#include "Precompiled.h"
#include "SphereCollider.h"
#include "AxisAlignedBoundingBox.h"

using namespace Vishv;
using namespace Physics;

META_DERIVED_BEGIN(SphereCollider, Collider)
	META_FIELD_BEGIN
		META_FIELD(mRadius, "Raddius")
	META_FIELD_END
META_CLASS_END

Vishv::Physics::SphereCollider::SphereCollider(float radius)
	:mRadius(radius)
{
}

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