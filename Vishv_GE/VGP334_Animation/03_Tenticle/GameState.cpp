#include "GameState.h"

void GameState::Initialize()
{
	mCameraTransform.mPosition = { 0.0f, 5.0f, -20.0f };
	mCamera.SetPosition(mCameraTransform.mPosition);
	mCamera.SetTarget({ 0.0f, 0.0f, 1.0f });

	mTenticle = Vishv::Graphics::Meshbuilder::CreateBoneCylinder(11, 12, 3.0f, 1.0f, 4);
	mTenticleBuffer.Initialize(mTenticle);

	//setup the skeleton
	mTenticleSkeleton.AddBone();
	mTenticleSkeleton.GetBone()->offsetTransform = Vishv::Math::Matrix4::TranslateMatrix(Vishv::Math::Vector3(0.0f, -11.0f * 0.5f, 0.0f));
	mTenticleSkeleton.CreateBone(0)->offsetTransform = Vishv::Math::Matrix4::TranslateMatrix(Vishv::Math::Vector3(0.0f, (-11.0f * 0.5f) + 2.0f, 0.0f));
	mTenticleSkeleton.CreateBone(1)->offsetTransform = Vishv::Math::Matrix4::TranslateMatrix(Vishv::Math::Vector3(0.0f, (-11.0f * 0.5f) + 4.0f, 0.0f));
	mTenticleSkeleton.CreateBone(2)->offsetTransform = Vishv::Math::Matrix4::TranslateMatrix(Vishv::Math::Vector3(0.0f, (-11.0f * 0.5f) + 6.0f, 0.0f));
	mTenticleSkeleton.CreateBone(3)->offsetTransform = Vishv::Math::Matrix4::TranslateMatrix(Vishv::Math::Vector3(0.0f, (-11.0f * 0.5f) + 8.0f, 0.0f));
	mTenticleSkeleton.CreateBone(4);

	mTenticleTransformation.SetRotation(Vishv::Math::Quaternion::RotationQuaternion(0.0f, { 1.0f,0.0f,0.0f }));
	mTenticleTransformation.mPosition.y = -5.0f;

	float boneHeight = 2.0f;
	for (size_t i = 0; i < mTenticleSkeleton.GetBoneArray().size(); ++i)
	{
		Vishv::Math::Vector3 v = { 0.0f, boneHeight * i, 0.0f };
		//mTenticleSkeleton.GetBoneArray()[i]->offsetTransform = Vishv::Math::Matrix4::TranslateMatrix(v);// .mTransform.mPoint.y = boneHeight * i;
		//mTenticleSkeleton.GetBoneArray()[i].mTransform.mQuaternion = Vishv::Math::Quaternion::RotationQuaternion(15.0f * i, { 0.0f, 0.0f, 1.0f });
	}

	mDiffuseMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("uvReference.jpg");
	mSpecularMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth_spec.jpg");
	mDisplacementMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth_bump.jpg");
	mNormalMap = Vishv::Graphics::TextureManager::Get()->LoadTexture("earth_normal.jpg");

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mOptionsBuffer.Initialize();
	mBoneTransformBuffer.Initialize();

	Vishv::Math::Vector3 dir(1.0f, -1.0f, 1.0f);
	mLight.direction = Vishv::Math::Normalize(dir);
	mLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mLight.diffuse = { 0.6f, 0.6f, 0.6f, 1.0f };
	mLight.specular = { 0.1f, 0.1f, 0.1f, 1.0f };

	mMaterial.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mMaterial.diffuse = { 0.8f, 0.7f, 0.1f, 1.0f };
	mMaterial.specular = { 0.2f, 0.2f, 0.2f, 1.0f };
	mMaterial.power = 10.0f;

	auto em = Vishv::Graphics::EffectsManager::Get();
	auto effect = Vishv::Graphics::EffectType::Skinning;
	em->GetBufferData(effect)->GetLightData()->ambient = mLight.ambient;
	em->GetBufferData(effect)->GetLightData()->diffuse = mLight.diffuse;
	em->GetBufferData(effect)->GetLightData()->position_Direction = mLight.direction;
	em->GetBufferData(effect)->GetLightData()->specular = mLight.specular;

	em->GetBufferData(effect)->GetMaterialData()->ambient = mMaterial.ambient;
	em->GetBufferData(effect)->GetMaterialData()->diffuse = mMaterial.diffuse;
	em->GetBufferData(effect)->GetMaterialData()->power = mMaterial.power;
	em->GetBufferData(effect)->GetMaterialData()->specular = mMaterial.specular;

	em->GetBufferData(effect)->GetOptionsData()->displacement = mOptionsData.displacement;
	em->GetBufferData(effect)->GetOptionsData()->isNormal = mOptionsData.isNormal;

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

	mCamera.SetPosition(mCameraTransform.mPosition);

	if (Vishv::Input::InputSystem::Get()->IsKeyDown(Vishv::Input::KeyCode::ESCAPE))
	{
		VishvApp::ShutDown();
		return;
	}
}

void GameState::Render()
{
	auto em = Vishv::Graphics::EffectsManager::Get();
	auto effect = Vishv::Graphics::EffectType::Skinning;
	em->BindEffect(effect);

	auto view = scene.sceneCamera->GetViewMatrix();
	auto proj = scene.sceneCamera->GetPerspectiveMatrix();
	auto world = (Vishv::Math::Matrix4::TranslateMatrix(mTenticleTransformation.Position()) * Vishv::Math::Matrix4::RotateMatrix(mTenticleTransformation.Rotation()));

	em->GetBufferData(effect)->GetTransform()->viewPosition = scene.sceneCamera->GetPosition();
	em->GetBufferData(effect)->GetTransform()->world = world.Transpose();
	em->GetBufferData(effect)->GetTransform()->wvp = (world * view * proj).Transpose();

	for (size_t i = 0; i < mTenticleSkeleton.GetBoneArray().size() && i < mTenticleSkeleton.MaxBoneCount(); ++i)
	{
		em->GetBufferData(effect)->GetBonetransformData()->boneTransforms[i] = (mTenticleSkeleton.bones[i]->offsetTransform * mTenticleSkeleton.GetTransformation(i)).Transpose();
	}

	em->Set(effect);
	em->BindBuffer(effect);

	Vishv::Graphics::TextureManager::Get()->GetTexture(mDiffuseMap)->BindPS(0);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mSpecularMap)->BindPS(1);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mDisplacementMap)->BindVS(2);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mNormalMap)->BindPS(3);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	mTenticleBuffer.Render();
}

void GameState::BoneSetting(int boneId)
{
	auto bone = mTenticleSkeleton.GetBone(boneId);
	if (bone == nullptr)
		return;

	std::string title = "bone " + std::to_string(boneId);
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

void GameState::GlobalDegubUI()
{
	ImGui::Begin("Global Control", 0, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::DragFloat3("Position##CameraTransform", &mCameraTransform.mPosition.x, 0.1f);

		static Vishv::Math::Vector3 rot;
		static Vishv::Math::Vector3  rotNew;
		if (ImGui::DragFloat3("RotationXYZ##CameraTransform", &rotNew.x, 0.1f))
		{
			mCameraTransform.RotateX(rotNew.x - rot.x);
			mCameraTransform.RotateY(rotNew.y - rot.y);
			mCameraTransform.RotateZ(rotNew.z - rot.z);
			rot = rotNew;
		}




		/*if (!(mCameraPositionNew == mCameraTransform.mPoint))
		{
			mCamera.SetPosition(mCameraPosition);
		}

		if (!(mCameraRotationNew == mCameraTransform.mQuaternion))
		{

			mCamera.Yaw(rotationY);
			mCamera.Pitch(rotationX);
		}*/
	}

	//auto bg = mBGColor;
	//ImGui::ColorEdit4("BG_Color##options", &bg.r);
	//if (!(bg == mBGColor))
	//{
	//	mBGColor = bg;
	//	Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);
	//}

	ImGui::End();
}

void GameState::RenderDebugUI()
{
	ImGui::Begin("Settings", 0, ImGuiWindowFlags_AlwaysAutoResize);
	static int id;
	static float height;
	ImGui::SliderInt("parentID", &id, -1, 10);
	if (ImGui::Button("Add bone"))
	{
		if (id < 0 || mTenticleSkeleton.GetBoneArray().empty())
			mTenticleSkeleton.AddBone();
		else
			mTenticleSkeleton.CreateBone(id);
	}
	//auto skel = mSkeleton.GetBoneArray();
	for (size_t i = 0; i < mTenticleSkeleton.GetBoneArray().size(); ++i)
	{
		BoneSetting(mTenticleSkeleton.GetBoneArray()[i]->index);
	}
	ImGui::End();
}

void GameState::RenderSimpleDraw()
{
}

void GameState::Terminate()
{

}

