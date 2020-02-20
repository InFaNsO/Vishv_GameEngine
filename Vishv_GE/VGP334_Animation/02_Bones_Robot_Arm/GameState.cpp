#include "GameState.h"

void GameState::Initialize()
{
	mCameraTransform.mPosition = { 0.0f, 5.0f, -10.0f };
	scene.sceneCamera->SetPosition(mCameraTransform.mPosition);
	scene.sceneCamera->SetTarget({0.0f, 0.0f, 1.0f});

	mBoneMesh = Vishv::Graphics::Meshbuilder::CreateCubeUV(3.0f, 5.0f, 7.0f);
	mBoneBuffer.Initialize(mBoneMesh);

	meshOffset = Vishv::Math::Matrix4::TranslateMatrix({ 0.0f, 1.5f,0.0f, 0.0f });

	mBoneTex = Vishv::Graphics::TextureManager::Get()->LoadTexture("skybox2.jpg");
	mTextureBuffer.Initialize();
}

void GameState::UpdateCamera(float deltaTime)
{
	const float moveSpeed = 0.1f;
	const float turnSpeed = 0.10f;
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::W))
		scene.sceneCamera->Walk(moveSpeed * deltaTime);
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::S))
		scene.sceneCamera->Walk(-moveSpeed * deltaTime);
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::D))
		scene.sceneCamera->Strafe(moveSpeed * deltaTime);
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::A))
		scene.sceneCamera->Strafe(-moveSpeed * deltaTime);
	if (Vishv::Input::InputSystem::Get()->IsMouseDown(Vishv::Input::MouseButton::RBUTTON))
	{
		scene.sceneCamera->Yaw(Vishv::Input::InputSystem::Get()->GetMouseMoveX()   * turnSpeed * deltaTime * Vishv::Math::Constans::DegToRad);
		scene.sceneCamera->Pitch(Vishv::Input::InputSystem::Get()->GetMouseMoveY() * turnSpeed * deltaTime * Vishv::Math::Constans::DegToRad);
	}
}

void GameState::Update(float deltaTime)
{
	const float moveSpeed = 0.1f;
	const float turnSpeed = 0.10f;
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::W))
		mCameraTransform.mPosition.z -= (moveSpeed * deltaTime);
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::S))
		mCameraTransform.mPosition.z += (moveSpeed * deltaTime);
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::D))
		mCameraTransform.mPosition.x += moveSpeed * deltaTime;
	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::A))
		mCameraTransform.mPosition.x += moveSpeed * deltaTime;

	//scene.sceneCamera->SetPosition(mCameraTransform.mPoint);

	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::ESCAPE))
	{
		VishvApp::ShutDown();
		return;
	}
}

void GameState::Render()
{
	auto em = Vishv::Graphics::EffectsManager::Get();
	em->BindEffect(Vishv::Graphics::EffectType::Texturing);

	auto view = scene.sceneCamera->GetViewMatrix();
	auto proj = scene.sceneCamera->GetPerspectiveMatrix();

	//extureBuffer.BindVS(0);

	for (size_t i = 0; i < mSkeleton.GetBoneArray().size(); ++i)
	{
		//Vishv::Math::Matrix4 m1(mSkeleton.GetBoneArray()[i].mTransform.mQuaternion);
		//auto m = m1 * Vishv::Math::Matrix4::TranslateMatrix(mSkeleton.GetBoneArray()[i].mTransform.mPoint);// *m1;// *m2;
		auto m = mSkeleton.GetTransformation(i);
		auto transform = Vishv::Math::Matrix4::Transpose(m *view * proj);
		//mTextureBuffer.Set({ transform });
		em->GetBufferData(Vishv::Graphics::EffectType::Texturing)->GetTextureing()->wvp = transform;
		em->Set(Vishv::Graphics::EffectType::Texturing);
		em->BindBuffer(Vishv::Graphics::EffectType::Texturing);

		Vishv::Graphics::TextureManager::Get()->GetTexture(mBoneTex)->BindPS(0);
		Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

		mBoneBuffer.Render();
	}
}

void GameState::BoneSetting(int boneId)
{
	auto bone = mSkeleton.GetBone(boneId);
	if (bone == nullptr)
		return;
	
	std::string title = "bone " + std::to_string(boneId) ;
	if (ImGui::CollapsingHeader(title.c_str()))
	{
		std::string off = "Offset##BoneTransform" + std::to_string(boneId);
		std::string ro = "Rotation##BoneTransform" + std::to_string(boneId);

		if (ImGui::DragFloat3(off.c_str(), &bone->posDebug.x, 1.0f) || ImGui::DragFloat3(ro.c_str(), &bone->rotDebug.x, 1.0f))
		{
			bone->toParentTransform = Vishv::Math::Quaternion::RotationQuaternion(bone->rotDebug.x * Vishv::Math::Constans::DegToRad, { 1.0f, 0.0f, 0.0f }) *
				Vishv::Math::Quaternion::RotationQuaternion(bone->rotDebug.y * Vishv::Math::Constans::DegToRad, { 0.0f, 1.0f, 0.0f }) *
				Vishv::Math::Quaternion::RotationQuaternion(bone->rotDebug.z * Vishv::Math::Constans::DegToRad, { 0.0f, 0.0f, 1.0f });

			bone->offsetTransform.SetTranslate(bone->posDebug);
		}
	}
}

void GameState::RenderDebugUI()
{
	ImGui::Begin("Settings", 0, ImGuiWindowFlags_AlwaysAutoResize);
	static int id;
	static float height;
	ImGui::SliderInt("parentID", &id, -1, 10);
	if (ImGui::Button("Add bone"))
	{
		if (id < 0 || mSkeleton.GetBoneArray().empty())
			mSkeleton.AddBone();
		else
			mSkeleton.CreateBone(id);
		//mSkeleton.GetBone()->offsetTransform = Vishv::Math::Matrix4::TranslateMatrix( { 0.0f, 1.5f, 0.0f, 0.0f });
	}
	//auto skel = mSkeleton.GetBoneArray();
	for (size_t i = 0; i < mSkeleton.GetBoneArray().size(); ++i)
	{
		BoneSetting(mSkeleton.GetBoneArray()[i]->index);
	}
	ImGui::End();
}

void GameState::RenderSimpleDraw()
{
	//Vishv::Graphics::SimpleDraw::AddSkeleton(mSkeleton, );
}

void GameState::Terminate()
{
	
}

