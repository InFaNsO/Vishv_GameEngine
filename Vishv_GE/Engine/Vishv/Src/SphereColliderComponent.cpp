#include "Precompiled.h"
#include "SphereColliderComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "GameObject.h"

#include "RigidBodyComponent.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(SphereCollider, Component)
	META_FIELD_BEGIN
		META_FIELD(mTag, "Tag")
		//META_FIELD(mColliderSphere, "Box")
	META_FIELD_END
META_CLASS_END

void Vishv::Components::SphereCollider::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mColliderSphere.myTransform = &mTransformComponent->Transform();
}

void Vishv::Components::SphereCollider::Update(float deltaTime)
{
	if (!firstUpdate)
		DoFirstUpdate();
}

void Vishv::Components::SphereCollider::DebugUI()
{
}

void Vishv::Components::SphereCollider::SimpleDraw()
{
}

void Vishv::Components::SphereCollider::DoFirstUpdate()
{
	auto rb = GetOwner().GetComponent<Rigidbody>();

	if (rb)
		rb->SetCollider(&mColliderSphere);

	firstUpdate = true;
}

bool Vishv::Components::SphereCollider::IsStatic()
{
	if (mColliderSphere.myRigidBody)
	{
		return mColliderSphere.myRigidBody->mIsStatic;
	}
	return false;
}
