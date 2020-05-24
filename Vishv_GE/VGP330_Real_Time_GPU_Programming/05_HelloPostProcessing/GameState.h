#pragma once
#include <../Engine/Vishv/Inc/Vishv.h>

class GameState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderDebugUI() override;
	void Terminate() override;
	void RenderSimpleDraw() override;

private:		//Things different from lighting
	Vishv::Graphics::MeshPX mScreenMesh;
	Vishv::Graphics::MeshPX mGlowScreenMesh;
	Vishv::Graphics::MeshBuffer mScreenMeshBuffer;
	Vishv::Graphics::MeshBuffer mGlowScreenMeshBuffer;

	Vishv::Math::Vector3 mSaberPosition1;
	Vishv::Math::Vector3 mSaberPosition2;

	Vishv::Graphics::RenderTarget mRendertarget;
	Vishv::Graphics::RenderTarget mRendertarget1;
	Vishv::Graphics::RenderTarget mRendertarget2;

	//Vishv::Graphics::VertexShader mPostProcessingVertexShader;
	//Vishv::Graphics::PixelShader mPostProcessingPixelShader;

	//Vishv::Graphics::VertexShader mGlowVertexShader;
	//Vishv::Graphics::PixelShader mGlowPixelShader;

	//Vishv::Graphics::VertexShader mMergeVertexShader;
	//Vishv::Graphics::PixelShader mMergePixelShader;

	void RenderScene();
	void RenderSceneGlow();
	void MultiGlow();
	void PostProcess();

private:

	Vishv::Graphics::Camera mCamera;
	Vishv::Math::Vector3 mCameraPosition;
	Vishv::Math::Vector3 mCameraRotation;
	
	Vishv::Graphics::MeshPN mCylnder;
	Vishv::Graphics::MeshPC mCylnderC;
	Vishv::Graphics::MeshPX mDome;
	Vishv::Graphics::Mesh mEarth;

	Vishv::Graphics::MeshPX mLighSaber1;
	Vishv::Graphics::MeshPX mLighSaber2;

	Vishv::Graphics::MeshBuffer mDomeBuffer;
	Vishv::Graphics::MeshBuffer mCylnderBuffer;
	Vishv::Graphics::MeshBuffer mEarthBuffer;
	Vishv::Graphics::MeshBuffer mLighSaberBuffer1;
	Vishv::Graphics::MeshBuffer mLighSaberBuffer2;

	//Vishv::Graphics::VertexShader mVertexShader;
	//Vishv::Graphics::PixelShader mPixelShader;
	//Vishv::Graphics::VertexShader mTextureVertexShader;
	//Vishv::Graphics::PixelShader mTexturePixelShader;

	Vishv::Graphics::TextureID mDomeTex;
	Vishv::Graphics::TextureID mDiffuseMap;
	Vishv::Graphics::TextureID mSpecularMap;
	Vishv::Graphics::TextureID mDisplacementMap;		//displacement map
	Vishv::Graphics::TextureID mNormalMap;
	Vishv::Graphics::TextureID mLightSaberTexture1;
	Vishv::Graphics::TextureID mLightSaberTexture2;


	struct TransformData					//This should match the constant buffer in the shader
	{
		Vishv::Math::Matrix4 world;
		Vishv::Math::Matrix4 wvp;
		Vishv::Math::Vector4 viewPosition;
	};
	struct OptionsData
	{
		Vishv::Math::Vector4 v;
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

	float timmer;

	OptionsData mOptionsData;
	Vishv::Math::Vector3 mPosition;
	Vishv::Math::Vector3 mRotation;

	Vishv::Graphics::Color mBGColor;

	int mCount = 5;
			
	//Lighting
	Vishv::Graphics::DirectionalLight mLight;
	Vishv::Graphics::Material mMaterial;
};
