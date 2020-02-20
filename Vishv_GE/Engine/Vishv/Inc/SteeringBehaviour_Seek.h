#ifndef INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_SEEK_H
#define INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_SEEK_H

#include "Common.h"
namespace Vishv::Components
{
	class AIAgent;
}

namespace Vishv::AI::Steering
{

	class Seek : public BehaviourBase<Components::AIAgent>
	{
	public:
		Vishv::Math::Vector3 Calculate(Components::AIAgent& agent) override;
		SteeringType GetType() const override { return SteeringType::Seek; }

	private:
		SteeringType mSteeringType = SteeringType::Seek;
	};
}
#endif //defined INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_ARRIVE_H
