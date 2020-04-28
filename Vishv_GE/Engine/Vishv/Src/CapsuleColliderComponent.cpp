#include "Precompiled.h"
#include "CapsuleColliderComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "GameObject.h"

#include "RigidBodyComponent.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(CapsuleCollider, Component)
META_FIELD_BEGIN
META_FIELD(mTag, "Tag")
//META_FIELD(mColliderCapsule, "Box")
META_FIELD_END
META_CLASS_END

void Vishv::Components::CapsuleCollider::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mColliderCapsule.myTransform = &mTransformComponent->Transform();
}

void Vishv::Components::CapsuleCollider::Update()
{
	if (!firstUpdate)
		DoFirstUpdate();
}

void Vishv::Components::CapsuleCollider::DebugUI()
{
}

void Vishv::Components::CapsuleCollider::SimpleDraw()
{
}

void Vishv::Components::CapsuleCollider::DoFirstUpdate()
{
	auto rb = GetOwner().GetComponent<Rigidbody>();

	if (rb)
		rb->SetCollider(&mColliderCapsule);

	firstUpdate = true;
}

bool Vishv::Components::CapsuleCollider::IsStatic()
{
	if (mColliderCapsule.myRigidBody)
	{
		return mColliderCapsule.myRigidBody->mIsStatic;
	}
	return false;
}
