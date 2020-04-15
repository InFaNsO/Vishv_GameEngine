#pragma once
#include <Vishv/Inc/Vishv.h>

class PlayState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void RenderSimpleDraw();
	void RenderDebugUI() override;
	void Render() override;
	void Terminate() override;
private:
	Vishv::GameWorld myGameWorld;

};

