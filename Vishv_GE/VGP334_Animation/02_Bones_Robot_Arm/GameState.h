#pragma once
#include <Vishv/Inc/Vishv.h>

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
	void UpdateCamera(float deltaTime);
	void BoneSetting(int boneId);
	void GlobalDegubUI();

	Vishv::Graphics::Camera mCamera;
	Vishv::Math::Transform mCameraTransform;

	Vishv::Graphics::TextureID mBoneTex;
	Vishv::Graphics::Skeleton mSkeleton;
	Vishv::Graphics::MeshPX mBoneMesh;
	Vishv::Graphics::MeshBuffer mBoneBuffer;

	Vishv::Math::Matrix4 meshOffset;

	using TextureBuffer = Vishv::Graphics::TypedConstantBuffer<Vishv::Math::Matrix4>;
	TextureBuffer mTextureBuffer;
};

 