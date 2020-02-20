#ifndef INCLUDED_VISHV_AI_STEERING_MODULE_H
#define INCLUDED_VISHV_AI_STEERING_MODULE_H

#include "SteeringBehaviour.h"

namespace Vishv::AI
{
	template<class AgentType>
	class SteeringModule
	{
	public:
		//META_CLASS_DECLARE

		void Initialize(AgentType& agent)
		{
			mAgent = &agent;

			mBehaviours.emplace_back(std::make_unique<Steering::Arrive>());
			mBehaviours.emplace_back(std::make_unique<Steering::Evade>());
			mBehaviours.emplace_back(std::make_unique<Steering::Flee>());
			mBehaviours.emplace_back(std::make_unique<Steering::Flocking>());
			mBehaviours.emplace_back(std::make_unique<Steering::ObstacleAvoidance>());
			mBehaviours.emplace_back(std::make_unique<Steering::Pursuit>());
			mBehaviours.emplace_back(std::make_unique<Steering::Seek>());
			mBehaviours.emplace_back(std::make_unique<Steering::Wander>());
		}

		template<class BehaviourType, class = std::void_t<std::is_base_of<Steering::BehaviourBase<AgentType>, BehaviourType>>>
		void AddBehaviour()
		{
			mBehaviours.emplace_back(std::make_unique<BehaviourType>());
		}

		void SetBehaviour(SteeringType type, bool set)
		{
			for (auto& b : mBehaviours)
				if (b.get()->GetType() == type)
				{
					b->SetActive(set); break;
				}
		}
		void Purge()
		{
			mBehaviours.clear();
		}

		void Reset()
		{
			for (auto& b : mBehaviours)
				b->SetActive(false);
		}

		Vishv::Math::Vector3 Calculate()
		{
			Vishv::Math::Vector3 total;
			for (auto &b : mBehaviours)
			{
				if (b->IsActive())
					total += b->Calculate(*mAgent);
			}
			return total;
		}
	
	private:

		AgentType * mAgent;
		std::vector<std::unique_ptr<Steering::BehaviourBase<AgentType>>> mBehaviours;
	};

//	template <class AgentType>
//	META_CLASS_BEGIN(SteeringModule<AgentType>)
//		META_NO_FIELD
//	META_CLASS_END
}



#endif // !INCLUDED_VISHV_AI_STEERING_MODULE_H
