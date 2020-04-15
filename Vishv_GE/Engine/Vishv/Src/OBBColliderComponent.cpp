#include "Precompiled.h"
#include "OBBColliderComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "GameObject.h"

#include "RigidBodyComponent.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(OBBCollider, Component)
	META_FIELD_BEGIN
		META_FIELD(mTag, "Tag")
		//META_FIELD(mColliderOBB, "Box")
	META_FIELD_END
META_CLASS_END

void Vishv::Components::OBBCollider::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mColliderOBB.myTransform = &mTransformComponent->Transform();
}

void Vishv::Components::OBBCollider::Update(float deltaTime)
{
	if (!firstUpdate)
		DoFirstUpdate();
}

void Vishv::Components::OBBCollider::DebugUI()
{
}

void Vishv::Components::OBBCollider::SimpleDraw()
{
}

void Vishv::Components::OBBCollider::DoFirstUpdate()
{
	auto rb = GetOwner().GetComponent<Rigidbody>();

	if (rb)
		rb->SetCollider(&mColliderOBB);

	firstUpdate = true;
}

bool Vishv::Components::OBBCollider::IsStatic()
{
	if (mColliderOBB.myRigidBody)
	{
		return mColliderOBB.myRigidBody->mIsStatic;
	}
	return false;
}
