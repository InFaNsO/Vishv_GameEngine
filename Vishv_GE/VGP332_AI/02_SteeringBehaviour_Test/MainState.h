#pragma once
#include "Vishv/Inc/Vishv.h"
#include "AIObject.h"

class MainState : public Vishv::AppState
{
public:
	MainState() = default;
	void Initialize() override;
	void Update(float deltaTime) override;

	void Render() override;

	void RenderDebugUI() override;

	void Terminate() override;
	void RenderSimpleDraw() override;

private:
	void AgentUI(Vishv::AI::Agent& agent);
	void WorldUI();

	Vishv::AI::Graph mGraph;
	Vishv::AI::GraphSearch mGSearch;

	Vishv::AI::Agent agentTestAgent;
	Vishv::AI::SteeringModule agentTestSteeringModule;

	Vishv::Math::Shapes::Capsule obstacle;
	Vishv::Math::Shapes::Cuboid wall;

	//AiObject mAgents;
	std::vector<AiObject> mAgents;
	Vishv::AI::World mAIWorld;
	const size_t maxAgents = 2;

	Vishv::Math::Vector3 targetPos;

	Vishv::Graphics::Color obstacleColor = Vishv::Graphics::Colors::BlueViolet;
	Vishv::Graphics::Color wallColor = Vishv::Graphics::Colors::Coral;
};


