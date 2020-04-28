#include "Precompiled.h"
#include "RigidBodyComponent.h"

#include "TransformComponent.h"
#include "PhysicsWorldService.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(Rigidbody, Component)
META_FIELD_BEGIN
META_FIELD_END
META_CLASS_END

void Vishv::Components::Rigidbody::Initialize()
{
	auto transformComp = GetOwner().GetComponent<TransformComponent>();
	
	if(transformComp)
		mRigidBody.myTransform = &transformComp->Transform();

}

void Vishv::Components::Rigidbody::SetCollider(Physics::Collider* coll)
{
	mRigidBody.myCollider = coll;
}
