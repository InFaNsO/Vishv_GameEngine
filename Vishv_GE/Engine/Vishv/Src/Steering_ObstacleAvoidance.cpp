#include "Precompiled.h"
#include "SteeringBehaviour_ObstacleAvoidance.h"
#include "AIAgent.h"

using namespace Vishv::Components;

Vishv::Math::Vector3 Vishv::AI::Steering::ObstacleAvoidance::Calculate(AIAgent& agent)
{
	//Vishv::Math::Vector2 normVel = Vishv::Math::Normalize(agent.Velocity());
	//Vishv::Math::Vector2 sight1 = agent.Position() + (normVel * agent.SafeDistance());
	//Vishv::Math::Vector2 sight2 = agent.Position() + (normVel * (agent.SafeDistance() * 0.5f));
	//Vishv::Math::Vector2 desiredVelocity{ 0,0 };
	//
	//auto nearestCircle = FindNearestObstacle(agent, normVel);
	//auto nearestWall = FindNearestWall(agent, normVel);
	//
	//bool wall = LineIntersectsWall(agent, sight1, sight2, nearestWall);
	//if (nearestCircle.mCenter.x < 0 && nearestCircle.mCenter.y < 0)
	//{
	//	if (wall)
	//	{
	//		Data d = GetDistanceWall(agent.Position(), nearestWall);
	//		desiredVelocity = sight1 - d.point;
	//		desiredVelocity = Vishv::Math::Normalize(desiredVelocity);
	//		desiredVelocity *= agent.MaxSpeed();
	//		desiredVelocity /= agent.Mass();
	//		return desiredVelocity;
	//	}
	//	else 
	//		return { 0.0f, 0.0f };
	//}
	//
	//bool cir = LineIntersectsCircle(agent, sight1, sight2, nearestCircle);
	//Data d;
	//if (wall)
	//{
	//	d = GetDistanceWall(agent.Position(), nearestWall);
	//}
	//if (cir && wall)
	//{
	//	float distanceCircleS1 = Vishv::Math::Magnitude(nearestCircle.mCenter - sight1);
	//	float distanceWallS1 = Vishv::Math::Magnitude(d.point - sight1);
	//
	//	if (distanceCircleS1 < distanceWallS1)
	//	{
	//		desiredVelocity = sight1 - nearestCircle.mCenter;
	//	}
	//	else
	//	{
	//		desiredVelocity = sight1 - d.point;
	//	}
	//
	//	desiredVelocity = Vishv::Math::Normalize(desiredVelocity);
	//	desiredVelocity *= agent.MaxSpeed();
	//	desiredVelocity /= agent.Mass();
	//	return desiredVelocity;
	//
	//}
	//else if (cir)
	//{
	//	desiredVelocity = sight1 - nearestCircle.mCenter;
	//	desiredVelocity = Vishv::Math::Normalize(desiredVelocity);
	//	desiredVelocity *= agent.MaxSpeed();
	//	desiredVelocity = (desiredVelocity / agent.Mass());
	//	return desiredVelocity;
	//}
	//else if (wall)
	//{
	//	desiredVelocity = sight1 - d.point;
	//	desiredVelocity = Vishv::Math::Normalize(desiredVelocity);
	//	desiredVelocity *= agent.MaxSpeed();
	//	desiredVelocity /= agent.Mass();
	//	return desiredVelocity;
	//}
	
	return Math::Vector3();
	
}

/*
bool Vishv::AI::Steering::ObstacleAvoidance::LineIntersectsCircle(Agent& agent, Vishv::Math::Vector2 sight1, Vishv::Math::Vector2 sight2, Vishv::Math::Shapes::Circle obstacle)
{
	return Vishv::Math::Magnitude(obstacle.mCenter - sight1) <= obstacle.mRadius + agent.SafeDistance() * 0.5f||
		Vishv::Math::Magnitude(obstacle.mCenter - sight2) <= obstacle.mRadius + agent.SafeDistance() * 0.5f;
}
bool Vishv::AI::Steering::ObstacleAvoidance::LineIntersectsWall(Agent & agent, Vishv::Math::Vector2 sight1, Vishv::Math::Vector2 sight2, Vishv::Math::Shapes::LineSegment wall)
{
	Data d = GetDistanceWall(agent.Position(), wall);
	auto point = d.point;

	return Vishv::Math::Magnitude(point - sight1) <= agent.SafeDistance() * 0.5f ||
		Vishv::Math::Magnitude(point - sight2) <= agent.SafeDistance() *0.5f;
}

Vishv::Math::Shapes::Circle Vishv::AI::Steering::ObstacleAvoidance::FindNearestObstacle(Agent& agent, Vishv::Math::Vector2 direction)
{
	if (agent.World().GetObstacles().empty())
	{
		Vishv::Math::Shapes::Circle tempC;
		tempC.mRadius = -1;
		tempC.mCenter = { -1, -1 };
		return tempC;
	}

	Vishv::Math::Shapes::Circle nearestCircle = agent.World().GetObstacles().front();
	float nearestDistance = Vishv::Math::MagnitudeSqr(nearestCircle.mCenter - agent.Position());
	for (auto obstacle : agent.World().GetObstacles())
	{
		float distance = Vishv::Math::MagnitudeSqr(obstacle.mCenter - agent.Position());
		if (distance < nearestDistance)
		{
			auto heading = obstacle.mCenter - agent.Position();
			auto dot = Vishv::Math::Dot(heading, direction);
			if (dot > 0)
			{
				nearestCircle = obstacle;
				nearestDistance = distance;
			}
		}
	}
	return nearestCircle;
}
Vishv::AI::Steering::ObstacleAvoidance::Data Vishv::AI::Steering::ObstacleAvoidance::GetDistanceWall(Vishv::Math::Vector2 pos, Vishv::Math::Shapes::LineSegment wall)
{
	Vishv::Math::Vector2 a = pos;
	Vishv::Math::Vector2 b = wall.mFrom;
	Vishv::Math::Vector2 c = wall.mTo;
	float wallLength = Vishv::Math::Sqrt(Vishv::Math::Sqr(wall.mTo.x - wall.mFrom.x) + Vishv::Math::Sqr(wall.mTo.y - wall.mFrom.y));

	float area = Vishv::Math::Abs((a.x*(b.y - c.y) + b.x*(a.y - c.y) + c.x*(a.y - b.y)) * 0.5f);
	float h = ((area * 2) / wallLength);
	
	Vishv::Math::Vector2 point, dir;

	float dis = Vishv::Math::Sqrt(Vishv::Math::Sqr(h) + (Vishv::Math::Sqr(wall.mFrom.x - pos.x) + Vishv::Math::Sqr(wall.mFrom.y - pos.y)));
	dir = { wall.mTo.x - wall.mFrom.x, wall.mTo.y - wall.mFrom.y };
	Vishv::Math::Normalize(dir);
	dir *= dis;
	point = wall.mFrom + dir;
	Data d;
	d.distance = h;
	d.point = point;

	return d;
}
Vishv::Math::Shapes::LineSegment Vishv::AI::Steering::ObstacleAvoidance::FindNearestWall(Agent& agent, Vishv::Math::Vector2 direction)
{
	Vishv::Math::Shapes::LineSegment nearestWall = agent.World().GetWalls().front();
	Data d = GetDistanceWall(agent.Position(), nearestWall);
	float nearestDistance = d.distance;
	for (auto wall : agent.World().GetWalls())
	{
		Data it = GetDistanceWall(agent.Position(), wall);
		if (it.distance < nearestDistance)
		{
			Vishv::Math::Vector2 heading = it.point - agent.Position();
			float dot = Vishv::Math::Dot(heading, direction);
			if (dot > 0.0f)
			{
				nearestWall = wall;
				nearestDistance = it.distance;
			}
		}
	}
	return nearestWall;
}

*/
