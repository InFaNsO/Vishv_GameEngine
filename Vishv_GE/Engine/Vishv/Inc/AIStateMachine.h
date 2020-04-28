#ifndef INCLUDED_VISHV_COMPONENT_AISTATEMACHINE_COMPONENT
#define INCLUDED_VISHV_COMPONENT_AISTATEMACHINE_COMPONENT

#include "Component.h"

class Vishv::GameObject;

namespace Vishv::Components
{
	
	//class Camera;	Camera Component

	class AIStateMachine : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update() override;
		void SimpleDraw() override;
		void DebugUI() override;
		void Terminate() override;

		void ChangeState(std::string&& name)
		{
			mStateMachine->ChangeState(name);
		}

		template<class State, class = std::void_t<std::is_base_of<AI::FSM::State<GameObject>, State>>>
		void AddState(std::string&& name)
		{
			mStateMachine->AddState<State>(std::move(name));
		}

		template<class State, class = std::void_t<std::is_base_of<AI::FSM::State<GameObject>, State>>>
		void AddState(std::unique_ptr<State> s, std::string&& name)
		{
			mStateMachine->AddState(std::move(s), std::move(name));
		}

	private:
		//other functions
		std::unique_ptr<AI::FSM::StateMachine<GameObject>> mStateMachine;
	};
}


#endif // !INCLUDED_VISHV_COMPONENT_AISTATEMACHINE_COMPONENT




