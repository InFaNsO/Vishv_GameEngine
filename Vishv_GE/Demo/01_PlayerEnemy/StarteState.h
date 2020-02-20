#pragma once
#include <Vishv/Inc/Vishv.h>

class StarteState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void RenderSimpleDraw();
	void RenderDebugUI() override;
	void Render() override;
	void Terminate() override;
private:
	bool shouldStart = false;
};

