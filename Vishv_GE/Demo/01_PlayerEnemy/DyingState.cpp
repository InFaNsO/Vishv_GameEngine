#include "DyingState.h"
#include "AnimationStates.h"

void DyingState::Enter(Vishv::GameObject & agent)
{
	agent.GetComponent<Vishv::Components::AISteering>()->ResetModule();
	agent.GetComponent<Vishv::Components::ModelAnimation>()->ChangeAnimation((size_t)AnimationStates::Dying);
}

void DyingState::Update(Vishv::GameObject & agent, float deltaTime)
{
}

void DyingState::Exit(Vishv::GameObject & agent)
{
}

