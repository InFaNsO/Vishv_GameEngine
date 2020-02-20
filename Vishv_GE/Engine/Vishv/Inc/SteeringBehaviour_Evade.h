#ifndef INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_EVADE_H
#define INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_EVADE_H

#include "Common.h"
namespace Vishv::Components
{
	class AIAgent;
}

namespace Vishv::AI::Steering
{

	class Evade : public BehaviourBase<Components::AIAgent>
	{
	public:
		Vishv::Math::Vector3 Calculate(Components::AIAgent& agent) override;
		SteeringType GetType() const override { return mSteeringType; }

	private:
		SteeringType mSteeringType = SteeringType::Evade;
	};
}
#endif //defined INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_ARRIVE_H
