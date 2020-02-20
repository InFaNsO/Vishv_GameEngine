#include"Precompiled.h"
#include "SteeringBehaviour_Arrive.h"
#include "AIAgent.h"

using namespace Vishv::Components;

Vishv::Math::Vector3 Vishv::AI::Steering::Arrive::Calculate(AIAgent & agent)
{
	Vishv::Math::Vector3 desiered, steer;
	desiered = (agent.Target() - agent.Position());
	desiered /= agent.Mass();
	desiered *= agent.MaxSpeed();
	return desiered;
}