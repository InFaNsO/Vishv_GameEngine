#include "Precompiled.h"
#include "SteeringBehaviour_Evade.h"

#include "AIAgent.h"
#include "TransformComponent.h"

using namespace Vishv::Components;

Vishv::Math::Vector3 Vishv::AI::Steering::Evade::Calculate(AIAgent & agent)
{
	if (agent.Neighbours().size() == 0)
		return Math::Vector3();

	AIAgent* nearest = agent.Neighbours()[0];
	float nearestDisSq = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(agent.Position() - nearest->Position()));

	for (size_t i = 1; i < agent.Neighbours().size(); ++i)
	{
		float distSq = Vishv::Math::Abs(Vishv::Math::MagnitudeSqr(agent.Position() - agent.Neighbours()[i]->Position()));
		if (distSq < nearestDisSq)
		{
			nearestDisSq = distSq;
			nearest = agent.Neighbours()[i];
		}
	}

	Math::Vector3 predictedPos = nearest->Position() + (nearest->Forward() * nearest->MaxSpeed());
	
	return ((Vishv::Math::Normalize(predictedPos - agent.Position()) * agent.MaxSpeed()) - (agent.Forward() * agent.MaxSpeed())) / agent.Mass();
}
