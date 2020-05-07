#include "Precompiled.h"
#include "PhysicsWorldService.h"

#include "RigidBodyComponent.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(PhysicsSystem, Service)
	META_FIELD_BEGIN
		META_FIELD(mMaxObjectsInWorld, "Max_Objects_Handled")
		META_FIELD(mMaxObjectsProcessedByThread, "Max_Handeled_Once")
		META_FIELD(mGravity, "Gravity")
	META_FIELD_END
META_CLASS_END

void Vishv::PhysicsSystem::Initialize()
{
	mWorld.Initialize(mMaxObjectsInWorld, mMaxObjectsProcessedByThread);
	SetName("Physics System");

	//mWorld.mGravity = mGravity;
}

void Vishv::PhysicsSystem::Terminate()
{
}


void Vishv::PhysicsSystem::Update()
{
	mWorld.Update(Core::Time::Get()->DeltaTime());
}

void Vishv::PhysicsSystem::Render()
{
}

void Vishv::PhysicsSystem::DebugUI()
{
}

void Vishv::PhysicsSystem::Register(Components::Rigidbody& object)
{
	mWorld.Register(object.mRigidBody);
}


void Vishv::PhysicsSystem::SetGravity(const Math::Vector3& gravity)
{
	mGravity = gravity;
	//mWorld.SetGravity(gravity);
}
