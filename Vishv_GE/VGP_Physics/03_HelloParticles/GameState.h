#pragma once
#include <../Engine/Vishv/Inc/Vishv.h>

class GameState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void RenderDebugUI() override;
	void Terminate() override;
	void RenderSimpleDraw() override;

private:

//	Vishv::ParticleSystem mParticleSystem;
	Vishv::Graphics::Color mBGColor;

	Vishv::Graphics::Camera mCamera;
	Vishv::Math::Vector3 mCameraPosition;
	Vishv::Math::Vector3 mCameraRotation;
};

