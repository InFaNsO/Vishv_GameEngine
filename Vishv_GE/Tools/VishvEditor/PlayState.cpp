#include "PlayState.h"


void PlayState::Initialize()
{
	shouldStart = false;
}

void PlayState::Update(float deltaTime)
{
	if (shouldStart)
	{
		VishvApp::ChangeState("MainState");
		return;
	}
}

void PlayState::RenderSimpleDraw()
{
}

void PlayState::RenderDebugUI()
{
	ImGui::Begin("Start");
	if (ImGui::Button("Start Project", { 100,100 }))
	{
		shouldStart = true;
	}
	ImGui::End();
}

void PlayState::Render()
{
}

void PlayState::Terminate()
{
}

