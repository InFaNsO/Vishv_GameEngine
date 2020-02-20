#pragma once
#include <Vishv/Inc/Vishv.h>


class GameState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	
	void Render() override;

	void GlobalDegubUI();
	void BoneSetting(int boneId);
	void RenderDebugUI() override;
	
	void Terminate() override;
	void RenderSimpleDraw() override;

private:
	Vishv::Graphics::Camera mCamera;
	Vishv::Math::Transform mCameraTransform;

	Vishv::Graphics::Skeleton mTenticleSkeleton;
	Vishv::Graphics::BoneMesh mTenticle;
	Vishv::Graphics::MeshBuffer mTenticleBuffer;
	Vishv::Math::Transform mTenticleTransformation;

private:
	Vishv::Graphics::TextureID mDiffuseMap;
	Vishv::Graphics::TextureID mSpecularMap;
	Vishv::Graphics::TextureID mDisplacementMap;		//displacement map
	Vishv::Graphics::TextureID mNormalMap;

private:
	struct TransformData					//This should match the constant buffer in the shader
	{
		Vishv::Math::Matrix4 world;
		Vishv::Math::Matrix4 wvp;
		Vishv::Math::Vector4 viewPosition;
	};
	struct OptionsData
	{
		float displacement;
		float isNormal = 1.0f;
		float padding[2];
	};
	struct BoneTransformData
	{
		Vishv::Math::Matrix4 boneTransforms[128];
	};

	using TransformBuffer = Vishv::Graphics::TypedConstantBuffer<TransformData>;
	using LightBuffer = Vishv::Graphics::TypedConstantBuffer<Vishv::Graphics::DirectionalLight>;
	using MaterialBuffer = Vishv::Graphics::TypedConstantBuffer<Vishv::Graphics::Material>;
	using OptionsBuffer = Vishv::Graphics::TypedConstantBuffer<OptionsData>;
	using BoneTransformBuffer = Vishv::Graphics::TypedConstantBuffer<BoneTransformData>;

	TransformBuffer mTransformBuffer;
	LightBuffer mLightBuffer;
	MaterialBuffer mMaterialBuffer;
	OptionsBuffer mOptionsBuffer;
	BoneTransformBuffer mBoneTransformBuffer;

	OptionsData mOptionsData;
	BoneTransformData mBoneTransformData;

	//Lighting
	Vishv::Graphics::DirectionalLight mLight;
	Vishv::Graphics::Material mMaterial;
};

