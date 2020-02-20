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
	Vishv::Graphics::Camera mCamera;
	Vishv::Math::Vector3 mCameraPosition;
	Vishv::Math::Vector3 mCameraRotation;

	Vishv::Graphics::Mesh mMesh;
	Vishv::Graphics::MeshPX mMeshPX	;
	Vishv::Graphics::MeshBuffer mMeshBuffer;
	Vishv::Graphics::TextureID mDiffuseMap;
	Vishv::Math::Matrix4 mLamboMat;
	Vishv::Math::Vector3 mLamboPos;
	Vishv::Math::Vector3 mLamboRot;

	//Vishv::Math::Matrix4 world
	//Vishv::Graphics::TextureID mSpecularMap;
	//Vishv::Graphics::TextureID mDisplacementMap;
	//Vishv::Graphics::TextureID mNormalMap;
	Vishv::Graphics::Color mBGColor;
	
	struct TextureData
	{
		Vishv::Math::Matrix4 wvp;
	};

	using TextureBuffer = Vishv::Graphics::TypedConstantBuffer<TextureData>;

	TextureBuffer mTextureBuffer;
	Vishv::Graphics::VertexShader mTextureVertexShader;
	Vishv::Graphics::PixelShader mTexturePixelShader;

};

