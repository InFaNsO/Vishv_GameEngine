#include"Precompiled.h"
#include "SteeringBehaviour_Flee.h"
#include "AIAgent.h"

using namespace Vishv::Components;

Vishv::Math::Vector3 Vishv::AI::Steering::Flee::Calculate(AIAgent & agent)
{
	if (agent.Neighbours().size() == 0)
		return Math::Vector3();

	Math::Vector3 nearByVel;
	for (size_t i = 0; i < agent.Neighbours().size(); ++i)
	{
		nearByVel += agent.Neighbours()[i]->Forward() * agent.Neighbours()[i]->MaxSpeed();
	}
	if (nearByVel == Math::Vector3())
		return Math::Vector3();

	nearByVel.Normalize();

	Math::Vector3 desired(-nearByVel);

	desired *= agent.MaxSpeed();

	return (desired - (agent.Forward() * agent.MaxSpeed())) / agent.Mass();
}