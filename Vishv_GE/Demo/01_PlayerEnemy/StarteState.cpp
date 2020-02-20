#include "StarteState.h"


void StarteState::Initialize()
{
	shouldStart = false;
}

void StarteState::Update(float deltaTime)
{
	if (shouldStart)
	{
		VishvApp::ChangeState("MainState");
		return;
	}
}

void StarteState::RenderSimpleDraw()
{
}

void StarteState::RenderDebugUI()
{
	ImGui::Begin("Start");
	if (ImGui::Button("Start Project", {100,100}))
	{
		shouldStart = true;
	}
	ImGui::End();
}

void StarteState::Render()
{
}

void StarteState::Terminate()
{
}

