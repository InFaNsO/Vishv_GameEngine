#include "Precompiled.h"
#include "SteeringBehaviour_Wander.h"
#include "AIAgent.h"

using namespace Vishv::Components;

Vishv::Math::Vector3 Vishv::AI::Steering::Wander::Calculate(AIAgent & agent)
{
	Vishv::Math::Shapes::Sphere wander;
	float wanderBufferLength = 3.0f;

	//set the center of imaginary sphere 4 times ahead of the player & set radius to 4 times steps of min safe distance
	wander.mTransform.mPosition = agent.Position() + (agent.Forward() * agent.CalucalteLengthValue(wanderBufferLength));
	wander.mRadius = agent.CalucalteLengthValue(0.5f) * 4;

	//generate a random coordinate inside of circle's front hemisphere if varible is false it will be locked down to the xz plane
	Vishv::Math::Vector3 target;
	target.x = Vishv::Math::Random::ZeroToOne() * (2 * wander.mRadius) - wander.mRadius;
	target.z = Vishv::Math::Random::Float(0.0f, wander.mRadius);
	target.y = !agent.IsFlatSurface() ? Vishv::Math::Random::Float(-wander.mRadius, wander.mRadius) : 0.0f;

	target += wander.mTransform.mPosition;

	//agent.wanderTarget = target;

	//doo an arive for there
	Vishv::Math::Vector3 desired, steer;
	desired = (target - agent.Position()) * agent.MaxSpeed();
	steer = desired - agent.Forward() * agent.MaxSpeed();

	steer.Normalize();
	steer *= agent.MaxSpeed();
	steer /= agent.Mass();
	return steer;
}
