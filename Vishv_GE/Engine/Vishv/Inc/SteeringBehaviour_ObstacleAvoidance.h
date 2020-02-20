#ifndef INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_OBSTACLE_AVOIDANCE_H
#define INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_OBSTACLE_AVOIDANCE_H

#include "Common.h"
namespace Vishv::Components
{
	class AIAgent;
}


namespace Vishv::AI::Steering
{

	class ObstacleAvoidance : public BehaviourBase<Components::AIAgent>
	{
	public:
		Vishv::Math::Vector3 Calculate(Components::AIAgent& agent) override;
		SteeringType GetType() const override { return mSteeringType; }

	private:
		SteeringType mSteeringType = SteeringType::ObstacleAvoidance;
	};
}
#endif //defined INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_OBSTACLE_AVOIDANCE_H
