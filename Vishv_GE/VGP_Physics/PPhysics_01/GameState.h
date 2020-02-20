#pragma once
#include "Vishv/Inc/Vishv.h"

class GameState : Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void RenderSimpleDraw() override;
	void RenderDebugUI() override;
	void Terminate() override;

private:
	Vishv::Physics::World mPWorld;
};

