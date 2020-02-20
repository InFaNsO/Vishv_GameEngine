#ifndef INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_ARRIVE_H
#define INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_ARRIVE_H

#include "Common.h"

namespace Vishv::Components
{
	class AIAgent;
}

namespace Vishv::AI::Steering
{

	class Arrive : public BehaviourBase<Components::AIAgent>
	{
	public:
		Vishv::Math::Vector3 Calculate(Components::AIAgent& agent) override;
		SteeringType GetType() const override { return SteeringType::Arrive; }

	private:
		SteeringType mSteeringType = SteeringType::Arrive;
	};
}
#endif //defined INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_ARRIVE_H

