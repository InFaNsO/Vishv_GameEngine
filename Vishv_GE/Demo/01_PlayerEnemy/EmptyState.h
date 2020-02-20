#pragma once
#include "Vishv/Inc/Vishv.h"

class EmptyState : public Vishv::AI::FSM::State<Vishv::GameObject>
{
public:
	void Update(Vishv::GameObject& agent, float deltaTime) override;
	void DebugUI(Vishv::GameObject& agent) override;

private:

};


