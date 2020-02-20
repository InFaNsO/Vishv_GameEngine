#include "Precompiled.h"
#include "SteeringBehaviour_Flocking.h"
#include "AIAgent.h"

using namespace Vishv::Components;

Vishv::Math::Vector3 Vishv::AI::Steering::Flocking::Calculate(AIAgent & agent)
{
	if (agent.Neighbours().size() == 0)
		return Math::Vector3();

	//Align
	auto neighbors = agent.Neighbours();
	Math::Vector3 avgVel;
	for (auto neighbour : neighbors)
	{
		avgVel += neighbour->Forward() * neighbour->MaxSpeed();
	}
	if(avgVel != Vishv::Math::Vector3())
		avgVel.Normalize();
	else
	{
		avgVel = agent.Forward() * agent.MaxSpeed();
	}

	//Cohesion
	Math::Vector3 avgPosition;
	for (auto neighbor : neighbors)
	{
		avgPosition += neighbor->Position();
	}
	avgPosition /= (float)neighbors.size();
	Math::Vector3 positionDirection = avgPosition - agent.Position();

	//seperation 
	//take care of the distance and of the 

	float avgDistanceSq = 0.0f;
	Math::Vector3 avgDirection;

	for (auto neighbour : neighbors)
	{
		avgDirection += neighbour->Position() - agent.Position();
		avgDistanceSq += Math::Abs(Math::MagnitudeSqr(neighbour->Position() - agent.Position()));
	}

	float avgDist = sqrtf(avgDistanceSq);
	Math::Vector3 seperationDirection = -avgDirection;

	return Vishv::Math::Normalize(seperationDirection * avgDist + avgDirection + avgVel);
}