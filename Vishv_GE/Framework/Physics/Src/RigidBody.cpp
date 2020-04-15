#include "Precompiled.h"
#include "RigidBody.h"

#include "PhysicsWorld.h"
#include "CollisionData.h"
#include "Collider.h"

using namespace Vishv;
using namespace Math;
using namespace Physics;

META_DERIVED_BEGIN(RigidBody, PhysicsObject)
	META_FIELD_BEGIN
		META_FIELD(AngularResistance, "AngularResistance")
	META_FIELD_END
META_CLASS_END

void RigidBody::ApplyForceOnPoint(const Math::Vector3& force, const Math::Vector3& point)
{
	auto vec = point - myTransform->mPosition;
	accumilatedForce += Vector3::Project(force, vec);
	accumilatedTorque += vec.Cross(force);
}

void Vishv::Physics::RigidBody::Update(float deltaTime)
{
	PhysicsObject::Update(deltaTime);

	auto vel = AngularVelocity;
	accumilatedTorque -= AngularResistance;
	AngularAcceleration = accumilatedTorque * deltaTime * InvMass;

	AngularVelocity = prvAngleVel + AngularAcceleration * deltaTime;
	prvAngleVel = vel;

	//apply rotation to quaternion
	myTransform->Rotate( Quaternion::RotationQuaternion(AngularVelocity.x, XAxis)
					* Quaternion::RotationQuaternion(AngularVelocity.y, YAxis)
					* Quaternion::RotationQuaternion(AngularVelocity.z, ZAxis));
}

void Vishv::Physics::RigidBody::HandleCollision(RigidBody* other)
{
	float dt = 0.03f;

	auto data = myCollider->CheckCollision(*other->myCollider);

	if (!data.IsColliding)
		return;

	//this part is wrong check it.
	//add force to both of them
	ApplyForce(Velocity.Cross(other->Velocity).Normalized() * (1.0f / InvMass) * (Velocity / dt));
	other->ApplyForce(Velocity.Cross(Velocity).Normalized() * (1.0f / other->InvMass) * (other->Velocity / dt));

	//collision Resolution
	myTransform->mPosition += (myTransform->mPosition - other->myTransform->mPosition).Normalized() * data.distanceInsertion;
}
