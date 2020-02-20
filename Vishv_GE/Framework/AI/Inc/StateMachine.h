
#ifndef INCLUDED_VISHV_AI_FSM_STATE_MACHINE_H
#define INCLUDED_VISHV_AI_FSM_STATE_MACHINE_H

#include "State.h"

namespace Vishv::AI::FSM
{
	template <class AgentType>
	class StateMachine
	{
	public:
		StateMachine(AgentType& agent)
			:mAgent(agent)
		{
		}

		using StateType = State<AgentType>;

		template<class NewStateType>
		void AddState(std::unique_ptr<NewStateType> state, std::string&& name)
		{
			static_assert(std::is_base_of<StateType, NewStateType>(), "[State Machine] The Type is not child of State<AgentType>");
			auto[iter, sucess] = mStates.emplace(std::make_pair(name, std::move(state)));
			if (sucess && !mCurrentState)
			{
				mCurrentState = iter->second.get();
				mCurrentState->Enter(mAgent);
			}
		}

		template<class NewStateType>
		void AddState(std::string&& name)
		{
			static_assert(std::is_base_of<StateType, NewStateType>(), "[State Machine] The Type is not child of State<AgentType>");
			auto[iter, sucess] = mStates.emplace(name, std::make_unique<NewStateType>());
			if (sucess && !mCurrentState)
			{
				mCurrentState = iter->second.get();
				mCurrentState->Enter(mAgent);
			}
		}

		void Update(float deltaTime = 0.33f) { mCurrentState->Update(mAgent, deltaTime); }
		void SimpleDraw() { mCurrentState->SimpleDraw(mAgent); }
		void DebugUI() { mCurrentState->DebugUI(mAgent); }


		void ChangeState(const std::string& name)
		{
			bool found = false;
			for (auto&[type, state] : mStates)
			{
				if (type == name)
				{
					mCurrentState->Exit(mAgent);
					mCurrentState = state.get();
					mCurrentState->Enter(mAgent);
					return;
				}
			}
			VISHVASSERT(found, "[AI::FSM::StateMachine::ChangeState] Wrong name provided, State could not be found");
		}

		bool HasStates() { return mCurrentState; }

		void Purge()
		{
			mCurrentState->Exit(mAgent);
			mCurrentState = nullptr;

			mStates.clear();
		}

		~StateMachine()
		{
			VISHVASSERT(mStates.empty(), "[AI::FSM::STATEMACHINE] State machine not exited properly need to call purge");
		}

	private:
		using StateMap = std::unordered_map<std::string, std::unique_ptr<StateType>>;

		AgentType& mAgent;
		StateType* mCurrentState = nullptr;
		StateMap mStates;
	};
}

#endif // !INCLUDED_VISHV_AI_FSM_STATE_MACHINE_H


#pragma once
