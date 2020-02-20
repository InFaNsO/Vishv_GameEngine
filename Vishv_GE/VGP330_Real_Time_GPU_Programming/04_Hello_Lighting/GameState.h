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

	Vishv::Graphics::Camera mCamera;
	Vishv::Math::Vector3 mCameraPosition;
	Vishv::Math::Vector3 mCameraRotation;
	Vishv::Graphics::MeshPN mCylnder;
	Vishv::Graphics::MeshPC mCylnderC;
	Vishv::Graphics::MeshPX mDome;
	Vishv::Graphics::Mesh mEarth;
	Vishv::Graphics::MeshBuffer mDomeBuffer;
	Vishv::Graphics::MeshBuffer mCylnderBuffer;
	Vishv::Graphics::MeshBuffer mEarthBuffer;

	Vishv::Graphics::VertexShader mVertexShader;
	Vishv::Graphics::PixelShader mPixelShader;
	Vishv::Graphics::VertexShader mTextureVertexShader;
	Vishv::Graphics::PixelShader mTexturePixelShader;

	Vishv::Graphics::TextureID mDomeTex;
	Vishv::Graphics::TextureID mDiffuseMap;
	Vishv::Graphics::TextureID mSpecularMap;
	Vishv::Graphics::TextureID mDisplacementMap;		//displacement map
	Vishv::Graphics::TextureID mNormalMap;

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
	struct TextureData
	{
		Vishv::Math::Matrix4 wvp;
	};

	using TextureBuffer = Vishv::Graphics::TypedConstantBuffer<TextureData>;
	using TransformBuffer = Vishv::Graphics::TypedConstantBuffer<TransformData>;
	using LightBuffer = Vishv::Graphics::TypedConstantBuffer<Vishv::Graphics::DirectionalLight>;
	using MaterialBuffer = Vishv::Graphics::TypedConstantBuffer<Vishv::Graphics::Material>;
	using OptionsBuffer = Vishv::Graphics::TypedConstantBuffer<OptionsData>;

	TextureBuffer mTextureBuffer;
	TransformBuffer mTransformBuffer;
	LightBuffer mLightBuffer;
	MaterialBuffer mMaterialBuffer;
	OptionsBuffer mOptionsBuffer;

	OptionsData mOptionsData;
	Vishv::Math::Vector3 mPosition;
	Vishv::Math::Vector3 mRotation;

	Vishv::Graphics::Color mBGColor;

	//Lighting
	Vishv::Graphics::DirectionalLight mLight;
	Vishv::Graphics::Material mMaterial;
};
