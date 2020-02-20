#ifndef INCLUDED_VISHV_AI_FSM_STATE_H
#define INCLUDED_VISHV_AI_FSM_STATE_H

#include "World.h"

namespace Vishv::AI
{
	namespace FSM
	{
		template <class AgentType>
		class State
		{
		public:
			virtual void Enter(AgentType& agent) {};
			virtual void Update(AgentType& agent, float deltaTime) = 0;
			virtual void Exit(AgentType& agent) {}

			//Debug functions
			virtual void DebugUI(AgentType& agent) {};
			virtual void SimpleDraw(AgentType& agent) {}
		};
	}
}
#endif // !INCLUDED_VISHV_AI_FSM_STATE_H


#pragma once
