#include "GameState.h"

using namespace Vishv::Graphics;

void GameState::Initialize()
{
	scene.sceneCamera->SetPosition({ 0.0f, 0.0f, -30.0f });
	//scene.sceneCamera->SetDirection({ 0.0f, 0.0f, 1.0f });

	mBGColor = Vishv::Graphics::Colors::Aqua;

	Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);

	mCylnder = Vishv::Graphics::Meshbuilder::CreateSphereNormal(14, 14, 10.f);
	mDome = Vishv::Graphics::Meshbuilder::CreateSphereUV(14, 14, 500.0f);
	mDomeBuffer.Initialize(mDome);
	mEarth = Vishv::Graphics::Meshbuilder::CreateCylinder(11, 12, 3.0f, 1.0f);//  CreateSphere(512, 512, 10.f);
	mEarthBuffer.Initialize(mEarth);


	Vishv::Math::Vector3 dir(1.0f, -1.0f, 1.0f);

	mLight.direction =  Vishv::Math::Normalize(dir);
	mLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mLight.diffuse= { 0.6f, 0.6f, 0.6f, 1.0f };
	mLight.specular = { 0.1f, 0.1f, 0.1f, 1.0f };

	mMaterial.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mMaterial.diffuse = { 0.8f, 0.7f, 0.1f, 1.0f };
	mMaterial.specular = { 0.2f, 0.2f, 0.2f, 1.0f };
	mMaterial.power = 10.0f;

	mDomeTex = Vishv::Graphics::TextureManager::Get()->LoadTexture("NebulaHdr.png");
	mDiffuseMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth.jpg");
	mSpecularMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth_spec.jpg");
	mDisplacementMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth_bump.jpg");
	mNormalMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth_normal.jpg");
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = Vishv::Input::InputSystem::Get();
	inputSystem->Update();

	//CameraUpdate(cam);
	//MeshUpdate(mb);



	if (inputSystem->IsKeyDown(Vishv::Input::KeyCode::ESCAPE))
	{
		VishvApp::ShutDown();
		return;
	}

	const float moveSpeed = 0.1f;
	const float turnSpeed = 0.10f;
	if (inputSystem->IsKeyDown(Vishv::Input::KeyCode::W))
		scene.sceneCamera->Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(Vishv::Input::KeyCode::S))
		scene.sceneCamera->Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(Vishv::Input::KeyCode::D))
		scene.sceneCamera->Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(Vishv::Input::KeyCode::A))
		scene.sceneCamera->Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(Vishv::Input::MouseButton::RBUTTON))
	{
		scene.sceneCamera->Yaw(inputSystem->GetMouseMoveX()   * turnSpeed * deltaTime * Vishv::Math::Constans::DegToRad);
		scene.sceneCamera->Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime * Vishv::Math::Constans::DegToRad);
	}
}

void GameState::Render()
{
	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Texturing);

	auto view = scene.sceneCamera->GetViewMatrix();
	auto proj = scene.sceneCamera->GetPerspectiveMatrix();

	auto transform = Vishv::Math::Matrix4::Transpose(Vishv::Math::Matrix4::TranslateMatrix(scene.sceneCamera->GetPosition()) * view * proj);
	
	Vishv::Graphics::EffectsManager::Get()->GetBufferData(EffectType::Texturing)->GetTextureing()->wvp = transform;
	Vishv::Graphics::EffectsManager::Get()->Set(EffectType::Texturing);
	Vishv::Graphics::EffectsManager::Get()->BindBuffer(EffectType::Texturing);

	Vishv::Graphics::TextureManager::Get()->GetTexture(mDomeTex)->BindPS(0);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	Vishv::Graphics::RasterizerManager::Get()->ChangeState("FrontSolid");
	mDomeBuffer.Render();
	Vishv::Graphics::RasterizerManager::Get()->ChangeState("BackSolid");

	Vishv::Graphics::EffectsManager::Get()->BindEffect(EffectType::Standard);
	
	auto world = Vishv::Math::Matrix4::TranslateMatrix(mPosition) 
		* (Vishv::Math::Matrix4::RotateMatrixX(mRotation.x)
		* Vishv::Math::Matrix4::RotateMatrixY(mRotation.y)
		* Vishv::Math::Matrix4::RotateMatrixZ(mRotation.z));

	auto bufData = EffectsManager::Get()->GetBufferData(EffectType::Standard);

	bufData->GetTransform()->world = world.Transpose();
	bufData->GetTransform()->wvp = (world * view * proj).Transpose();
	bufData->GetTransform()->viewPosition = scene.sceneCamera->GetPosition();
	bufData->GetLightData()->ambient = mLight.ambient;
	bufData->GetLightData()->diffuse = mLight.diffuse;
	bufData->GetLightData()->position_Direction = mLight.direction;
	bufData->GetLightData()->specular = mLight.specular;
	bufData->GetMaterialData()->ambient = mMaterial.ambient;
	bufData->GetMaterialData()->diffuse = mMaterial.diffuse;
	bufData->GetMaterialData()->power = mMaterial.power;
	bufData->GetMaterialData()->specular = mMaterial.specular;
	bufData->GetOptionsData()->displacement = mOptionsData.displacement;
	bufData->GetOptionsData()->isNormal = mOptionsData.isNormal;

	EffectsManager::Get()->Set(EffectType::Standard);
	EffectsManager::Get()->BindBuffer(EffectType::Standard);

	Vishv::Graphics::TextureManager::Get()->GetTexture(mDiffuseMap)->BindPS(0);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mSpecularMap)->BindPS(1);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mDisplacementMap)->BindVS(2);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mNormalMap)->BindPS(3);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	mEarthBuffer.Render();
}

void GameState::RenderDebugUI()
{
	ImGui::Begin("Settings");
	if (ImGui::CollapsingHeader("Light"))
	{
		bool changed = false;
		changed |= ImGui::DragFloat("Direction X##Light", &mLight.direction.x, 0.01f, -1.0f, 1.0f);
		changed |= ImGui::DragFloat("Direction Y##Light", &mLight.direction.y, 0.01f, -1.0f, 1.0f);
		changed |= ImGui::DragFloat("Direction Z##Light", &mLight.direction.z, 0.01f, -1.0f, 1.0f);
		if (changed)
		{
			mLight.direction.Normalize();
		}
	ImGui::ColorEdit4("Ambient##Light", &mLight.ambient.x);
	ImGui::ColorEdit4("Diffuse##Light", &mLight.diffuse.x);
	ImGui::ColorEdit4("Specular##Light", &mLight.specular.x);
	}
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::ColorEdit4("Ambient##Material", &mMaterial.ambient.x);
		ImGui::ColorEdit4("Diffuse##Material", &mMaterial.diffuse.x);
		ImGui::ColorEdit4("Specular##Material", &mMaterial.specular.x);
		ImGui::DragFloat("Power##Material", &mMaterial.power);
	}
	if (ImGui::CollapsingHeader("Options"))
	{
		bool normal = mOptionsData.isNormal > 0.0f ? true : false;
		Vishv::Graphics::Color bg(mBGColor);
		ImGui::ColorEdit4("BG_Color##Material", &bg.r);
		ImGui::DragFloat("Displacement##options", &mOptionsData.displacement, 0.01f, 0.0f, 10.0f);
		ImGui::Checkbox("Normal##options", &normal);
		mOptionsData.isNormal = normal ? 1.0f : 0.0f;

		if (!(bg == mBGColor))
		{
			mBGColor = bg;
			Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);
		}
	}
	if (ImGui::CollapsingHeader("EarthTransform"))
	{
		ImGui::DragFloat3("Position##Transform", &mPosition.x, 0.1f);
		ImGui::DragFloat3("Rotation##Transform", &mRotation.x, 0.1f, -Vishv::Math::Constans::Pi, Vishv::Math::Constans::Pi);
	}
	if (ImGui::CollapsingHeader("CameraTransform"))
	{
		const float moveSpeed = 0.1f;
		const float turnSpeed = 0.10f;
		Vishv::Math::Vector3 mCameraPositionNew(mCameraPosition);
		Vishv::Math::Vector3 mCameraRotationNew(mCameraRotation);
		ImGui::DragFloat3("Position##Transform", &mCameraPositionNew.x, 0.1f);
		ImGui::DragFloat3("Rotation##Transform", &mCameraRotationNew.x, 0.1f, -Vishv::Math::Constans::Pi, Vishv::Math::Constans::Pi);

		if (!(mCameraPositionNew == mCameraPosition))
		{

		}

		if (!(mCameraRotationNew == mCameraRotation))
		{

		}
	}


	ImGui::End();
}

void GameState::RenderSimpleDraw()
{
//	Vishv::Graphics::SimpleDraw::AddLine(Vishv::Math::Vector3(), { 100.0f, 0.0f, 0.0f }, Vishv::Graphics::Colors::Red);
//	Vishv::Graphics::SimpleDraw::AddLine(Vishv::Math::Vector3(), { 0.0f, 100.0f, 0.0f }, Vishv::Graphics::Colors::Green);
//	Vishv::Graphics::SimpleDraw::AddLine(Vishv::Math::Vector3(), { 0.0f, 0.0f, 100.0f }, Vishv::Graphics::Colors::Yellow);
//
//	Vishv::Graphics::SimpleDraw::AddSphere({ 10.0f, 10.0f, 10.0f }, 50.0f, Vishv::Graphics::Colors::Black);

	//for (float i = 0; i < 50; ++i)
	//{
	//	Vishv::Graphics::SimpleDraw::AddLine({i, 0.0f, -50.0f}, { i, 0.0f, 50.0f }, Vishv::Graphics::Colors::DarkGray);
	//	Vishv::Graphics::SimpleDraw::AddLine({-50.0f, 0.0f, i}, { 50.0f, 0.0f, i }, Vishv::Graphics::Colors::DarkGray);
	//}
	//
	//Vishv::Graphics::SimpleDraw::Render(mCamera);
}

void GameState::Terminate()
{
	mTexturePixelShader.Terminate();
	mTextureVertexShader.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mCylnderBuffer.Terminate();
	mTransformBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTextureBuffer.Terminate();
}
