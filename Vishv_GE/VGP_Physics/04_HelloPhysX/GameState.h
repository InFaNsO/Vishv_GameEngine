#pragma once

#include <Vishv/Inc/Vishv.h>


class GameState : Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void RenderDebugUI() override;
	void Terminate() override;
	void RenderSimpleDraw() override;

private:

};

