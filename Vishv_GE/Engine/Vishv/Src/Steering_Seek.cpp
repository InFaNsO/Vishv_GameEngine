#include "Precompiled.h"
#include "SteeringBehaviour_Seek.h"
#include "AIAgent.h"

using namespace Vishv::Components;

Vishv::Math::Vector3 Vishv::AI::Steering::Seek::Calculate(AIAgent& agent)
{
	auto desierd = agent.Position() - agent.Target();
	auto vel = agent.Forward() * agent.MaxSpeed();
	auto returnVal = Vishv::Math::Normalize(vel - desierd) * agent.MaxSpeed();

	return returnVal;
	//return ((Vishv::Math::Normalize(agent.Target() - agent.Position()) * agent.MaxSpeed()) - (agent.Forward() * agent.MaxSpeed())) / agent.Mass();
}
