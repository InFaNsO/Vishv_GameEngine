#ifndef INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_H
#define INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_H

namespace Vishv::AI
{
	struct Agent;

	enum class SteeringType
	{
		base = -1,
		Arrive,
		Evade,
		Flee,
		Flocking,
		ObstacleAvoidance,
		Pursuit,
		Seek,
		Wander,
		count
	};

	namespace Steering
	{
		template<class AgentType>
		class BehaviourBase
		{
		public:
			virtual Vishv::Math::Vector3 Calculate(AgentType& agent) = 0;
			virtual SteeringType GetType()const = 0;
			void SetActive(bool set) { mIsActive = set; }
			bool IsActive() { return mIsActive; }
			void SetVariable(bool var) { variable = var; }

		protected:
			bool variable = false;
			bool mIsActive = false;
		};
	}
}

#endif // !INCLUDED_VISHV_AI_STEERINGBEHAVIOUR_H

