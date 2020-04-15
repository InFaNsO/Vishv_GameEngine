#include "Precompiled.h"
#include "PhysicsObject.h"

using namespace Vishv;
using namespace Physics;


META_CLASS_BEGIN(PhysicsObject)
	META_FIELD_BEGIN
		META_FIELD(mIsStatic, "Static")
		META_FIELD(InvMass, "InvMass")
		META_FIELD(Resistance, "Resistance")
	META_FIELD_END
META_CLASS_END

void Vishv::Physics::PhysicsObject::ApplyForce(const Math::Vector3& force)
{
	accumilatedForce += force;
}

void Vishv::Physics::PhysicsObject::Update(float deltaTime)
{
	auto vel = Velocity;
	accumilatedForce -= Resistance;
	Acceleration = accumilatedForce * deltaTime * InvMass;

	Velocity = prvVelocity + Acceleration * deltaTime;
	prvVelocity = vel;

	myTransform->mPosition += Velocity; 
}
