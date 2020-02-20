#include "MainState.h"
#include "PathFindingTool.h"
#include "DrawShapeTool.h"
#include "SteeringTool.h"

using namespace Vishv;
using namespace Vishv::AI;
using namespace Vishv::Math;

namespace
{
	UI::PathFindingTool pTool;
	UI::DrawShapeTool dsTool;
	UI::SteeringTool steerTool;
}



void MainState::Initialize()
{
	scene.sceneCamera->transform.mPosition = { 0.0f,0.0f, -20.0f };
	//scene.sceneCamera->transform.RotateX(-90.0f);
	pTool.Initialize(mGraph, mGSearch);
	dsTool.Initialize();

	agentTestSteeringModule.Initialize(agentTestAgent);
	//mAIWorld.Register(&agentTestAgent);
	agentTestAgent.world = &mAIWorld;

	//steerTool.Initialize(agentTestAgent, agentTestSteeringModule);

	//mAgents.mSteeringModule.Initialize(mAgents.aiAgent);

	mAgents.reserve(maxAgents);
	for (size_t i = 0; i < maxAgents; ++i)
	{
		mAgents.emplace_back(std::move(AiObject()));
		mAgents[i].aiAgent.mIndex = i;
		mAgents[i].aiAgent.world = &mAIWorld;
		mAIWorld.Register(&mAgents[i].aiAgent);
		mAgents[i].mSteeringModule.Initialize(mAgents[i].aiAgent);
		//mAgents[i].mSteeringModule.SetBehaviour(SteeringType::Flee, true);
		mAgents[i].mSteeringModule.SetBehaviour(SteeringType::Arrive, true);
		mAgents[i].aiAgent.transform.mPosition.x = (Vishv::Math::Random::ZeroToOne() * 15.0f) - 7.5f;
		mAgents[i].aiAgent.transform.mPosition.y = (Vishv::Math::Random::ZeroToOne() * 15.0f) - 7.5f;
		mAgents[i].aiAgent.transform.mPosition.z = (Vishv::Math::Random::ZeroToOne() * 15.0f) - 7.5f;
		mAgents[i].aiAgent.transform.RotateY((Vishv::Math::Random::ZeroToOne() * 120.0f) - 60.0f);
		mAgents[i].aiAgent.path.push_back(targetPos);
	}
}

void MainState::Update(float deltaTime)
{
	if (dsTool.GetWall(wall))
		mAIWorld.Register(wall);
	if (dsTool.GetObstacle(obstacle))
		mAIWorld.Register(obstacle);

	//agentTestAgent.transform.mPosition += agentTestSteeringModule.Calculate() * deltaTime * 0.3f;
	for (size_t i = 0; i < maxAgents; ++i)
		mAgents[i].Update(deltaTime);

}

void MainState::RenderSimpleDraw()
{
	//pTool.SimpleDraw();
	//dsTool.SimpleDraw();
	//steerTool.SimpleDraw();

	for (auto& obs : mAIWorld.GetObstacles())
		Graphics::SimpleDraw::AddCapsule(obs, obstacleColor);

	for (auto& walled : mAIWorld.GetWalls())
		Graphics::SimpleDraw::AddCuboid(walled, wallColor);

	Graphics::SimpleDraw::AddSphere(targetPos, 1.0f, Graphics::Colors::SeaGreen);

	//Graphics::SimpleDraw::AddSphere(agentTestAgent.transform.mPosition, 2.0f, Graphics::Colors::LimeGreen);
	for (size_t i = 0; i < maxAgents; ++i)
		mAgents[i].SimpleDraw();// Update(deltaTime);
}

void MainState::RenderDebugUI()
{
	//pTool.DrawUI();
	//dsTool.DrawUI();
	//steerTool.DrawUI();

	ImGui::Begin("AI Settings");

	if (ImGui::DragFloat3("Target", &targetPos.x, 0.1f))
	{
		for (size_t i = 0; i < maxAgents; ++i)
			mAgents[i].aiAgent.path.front() = targetPos;
	}
	//AgentUI(agentTestAgent);
	WorldUI();


	ImGui::End();
}

void MainState::AgentUI(Vishv::AI::Agent & agent)
{
	if (!ImGui::CollapsingHeader("Agent Settings"))
		return;
	ImGui::DragFloat3("Position##AGENTSET", &agent.transform.mPosition.x, 0.1f);
	ImGui::DragFloat3("Velocity##AGENTSET", &agent.velocity.x, 0.1f);
	ImGui::DragFloat("Mass##AGENTSET", &agent.mass, 0.1f);
	ImGui::DragFloat("Safe Distance##AGENTSET", &agent.safeDistanceMin, 0.1f);
	ImGui::DragFloat("Safe Distance Steps##AGENTSET", &agent.safeDistanceSteps, 0.1f);
	ImGui::DragFloat("Neighbour Distance##AGENTSET", &agent.safeDistanceSteps, 0.1f);
	ImGui::DragFloat("Max Speed##AGENTSET", &agent.maxSpeed, 0.1f);
	ImGui::Checkbox("Is on flat surface##AGENTSET", &agent.isOnFlatSurface);
}

void MainState::WorldUI()
{
	if (ImGui::CollapsingHeader("World"))
	{
		ImGui::ColorEdit4("Obstacle Color##aiworld", &obstacleColor.x);
		ImGui::ColorEdit4("Wall Color##aiworld", &wallColor.x);

		if (ImGui::Button("Save##aiworld"))
		{
			Vishv::AI::WorldIO::Save("world.vworld", mAIWorld);
		}
		if (ImGui::Button("Load##aiworld"))
		{
			Vishv::AI::WorldIO::Load("world.vworld", mAIWorld);
		}
	}

	//add ability to change existing things in world
}


void MainState::Render()
{

}


void MainState::Terminate()
{
}
