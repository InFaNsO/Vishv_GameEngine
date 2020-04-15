#include "Precompiled.h"
#include "Collider.h"
#include "AxisAlignedBoundingBox.h"
#include "CollisionData.h"

#include "RigidBody.h"

using namespace Vishv;
using namespace Vishv::Physics;

META_CLASS_BEGIN(Collider)
	META_FIELD_BEGIN
		META_FIELD(mIsTrigger, "IsTrigger")
		//META_FIELD(myRigidBody, "RigidBody")
	META_FIELD_END
META_CLASS_END

bool Vishv::Physics::Collider::IsTrigger()
{
	return mIsTrigger;
}

CollisionData Vishv::Physics::Collider::CheckCollision(Collider& other) const
{
	return CollisionData();
}

