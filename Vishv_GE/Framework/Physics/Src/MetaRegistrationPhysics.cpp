#include "Precompiled.h"
#include "MetaRegistrationPhysics.h"

#include "Collider.h"
#include "OrientedBoundingBox.h"
#include "SphereCollider.h"

#include "PhysicsObject.h"
#include "RigidBody.h"

void Vishv::Physics::StaticMetaRegister()
{
	//Physics Classes
	META_REGISTER(PhysicsObject);
	META_REGISTER(RigidBody);

	//collider classes
	META_REGISTER(Collider);
	META_REGISTER(OBB);
	META_REGISTER(SphereCollider);

}

