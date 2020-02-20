#include "EmptyState.h"
#include "EnemyStates.h"

void EmptyState::Update(Vishv::GameObject & agent, float deltaTime)
{
}

void EmptyState::DebugUI(Vishv::GameObject & agent)
{
	ImGui::Text("Empty State");

	if (ImGui::Button("Start"))
		agent.GetComponent<Vishv::Components::AIStateMachine>()->ChangeState(ToString(EnemyStates::Wander));
}

