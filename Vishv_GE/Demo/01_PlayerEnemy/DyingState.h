#pragma once
#include "Vishv/Inc/Vishv.h"

class DyingState : public Vishv::AI::FSM::State<Vishv::GameObject>
{
public:
	void Enter(Vishv::GameObject& agent) override;
	void Update(Vishv::GameObject& agent, float deltaTime) override;
	void Exit(Vishv::GameObject& agent) override;

private:

};


