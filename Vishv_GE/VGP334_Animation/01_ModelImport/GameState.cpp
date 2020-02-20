#include "GameState.h"

using namespace Vishv;
using namespace Vishv::Graphics;

void GameState::Initialize()
{
	mCameraPosition = { 0.0f, 0.0f, -30.0f };
	mCamera.SetPosition(mCameraPosition);
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });

	std::filesystem::path path = "../../Assets/Shaders/Texturing.fx";
	mTexturePixelShader.Initialize(path);
	mTextureVertexShader.Initialize(path, Vishv::Graphics::VertexPX::Format);

	mBGColor = Vishv::Graphics::Colors::Aqua;

	Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);
	mTextureBuffer.Initialize();
	mDiffuseMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth.jpg");

	Vishv::Graphics::MeshIO io;
	 auto m = io.LoadMeshGeneral("mesh.vishmesh");
	// mMesh = m.value();
	 
	 mMeshPX.mVertices.reserve(mMesh.mVertices.size());
	 for (size_t i = 0; i < mMesh.mVertices.size(); ++i)
	 {
		 Vishv::Graphics::VertexPX v;
		 v.position = mMesh.mVertices[i].position;
		 v.u = mMesh.mVertices[i].texCoord.x;
		 v.v = mMesh.mVertices[i].texCoord.y;
		 mMeshPX.mVertices.emplace_back(v);
	 }
	 for (size_t i = 0; i < mMesh.mIndices.size(); ++i)
	 {
		 mMeshPX.mIndices.emplace_back(mMesh.mIndices[i]);
	 }

	 mMeshBuffer.Initialize(mMeshPX);
	 //mMeshBuffer.Initialize(sizeof(VertexPX), mMeshPX.mVertices.size(), mMeshPX.mVertices.data(), mMeshPX.mIndices.data(), mMeshPX.mIndices.size());

	 mLamboPos.z = 10.0f;
	 mLamboMat.Translate(mLamboPos);
}

void GameState::Update(float deltaTime)
{

}

void GameState::Render()
{
	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	auto view = mCamera.GetViewMatrix();
	auto proj = mCamera.GetPerspectiveMatrix();

	auto transform = Vishv::Math::Matrix4::Transpose(mLamboMat * view * proj);
	mTextureBuffer.Set({ transform });
	mTextureBuffer.BindVS(0);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mDiffuseMap)->BindPS(0);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	mMeshBuffer.Render();
}

void GameState::RenderSimpleDraw()
{

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

	ImGui::Begin("Model Control", 0, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Lamborgini"))
	{
		const float moveSpeed = 0.1f;
		const float turnSpeed = 0.10f;
		Vishv::Math::Vector3 mLamboPositionNew(mLamboPos);
		Vishv::Math::Vector3 mLamboRotationNew(mLamboRot);
		ImGui::DragFloat3("Position##LamboTransform", &mLamboPositionNew.x, 0.1f);
		ImGui::DragFloat3("Rotation##LamboTransform", &mLamboRotationNew.x, 0.1f);
		if (!(mLamboPositionNew == mLamboPos))
		{
			mLamboMat.Translate(mLamboPositionNew - mLamboPos);
			mLamboPos = mLamboPositionNew;
		}

		if (!(mLamboRotationNew == mLamboRot))
		{
			mLamboMat = Vishv::Math::Matrix4::Identity();
			mLamboMat = mLamboMat * Vishv::Math::Matrix4::RotateMatrixX(mLamboRotationNew.x - mLamboRot.x);
			mLamboMat = mLamboMat * Vishv::Math::Matrix4::RotateMatrixY(mLamboRotationNew.y - mLamboRot.y);
			mLamboMat = mLamboMat * Vishv::Math::Matrix4::RotateMatrixZ(mLamboRotationNew.z - mLamboRot.z);
			mLamboMat = mLamboMat * Vishv::Math::Matrix4::TranslateMatrix(mLamboPos);
			

			mLamboRot = mLamboRotationNew;
		}
	}
	ImGui::End();
}

void GameState::Terminate()
{

}
