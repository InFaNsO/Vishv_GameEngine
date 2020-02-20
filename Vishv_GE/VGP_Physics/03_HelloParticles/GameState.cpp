#include "GameState.h"

void GameState::Initialize()
{
	mCameraPosition = { 20.0f, 0.0f, -110.0f };
	mCamera.SetPosition(mCameraPosition);
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });

	mParticleSystem.Initialize();

	mBGColor = Vishv::Graphics::Colors::White;
	Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);
}

void GameState::Update(float deltaTime)
{
	mParticleSystem.Update(deltaTime);
}

void GameState::Render()
{
	mParticleSystem.Render(mCamera);
}
void GameState::RenderDebugUI()
{
	ImGui::Begin("Global Control", 0, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Camera"))
	{
		const float moveSpeed = 0.1f;
		const float turnSpeed = 0.10f;
		Vishv::Math::Vector3 mCameraPositionNew(mCameraPosition);
		Vishv::Math::Vector3 mCameraRotationNew(mCameraRotation);
		ImGui::DragFloat3("Position##CameraTransform", &mCameraPositionNew.x, 0.1f);
		ImGui::DragFloat3("Rotation##CameraTransform", &mCameraRotationNew.x, 0.1f, -Vishv::Math::Constans::Pi, Vishv::Math::Constans::Pi);
		if (!(mCameraPositionNew == mCameraPosition))
		{
			mCameraPosition = mCameraPositionNew;
			mCamera.SetPosition(mCameraPosition);
		}

		if (!(mCameraRotationNew == mCameraRotation))
		{
			float rotationY = mCameraRotationNew.y - mCameraRotation.y;
			float rotationX = mCameraRotationNew.x - mCameraRotation.x;
			mCameraRotation = mCameraRotationNew;

			mCamera.Yaw(rotationY);
			mCamera.Pitch(rotationX);
		}
	}
	
	auto bg = mBGColor;
	ImGui::ColorEdit4("BG_Color##options", &bg.r);
	if (!(bg == mBGColor))
	{
		mBGColor = bg;
		Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);
	}

	ImGui::End();
	
	mParticleSystem.RenderDebugUI();
}
void GameState::Terminate()
{
	mParticleSystem.Terminate();
}
void GameState::RenderSimpleDraw()
{
	mParticleSystem.RenderSimpleDraw(mCamera);
}
