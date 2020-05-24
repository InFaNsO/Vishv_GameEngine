#include "GameState.h"

void GameState::Initialize()
{
	scene.sceneCamera->SetPosition({ 0.0f, 5.0f, -30.0f });
	scene.sceneCamera->SetDirection({ 0.0f, -1.0f, 1.0f });

	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Standard);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Texturing);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Merge);

	//mPixelShader.Initialize("../../Assets/Shaders/Standard.fx");
	//mVertexShader.Initialize("../../Assets/Shaders/Standard.fx", Vishv::Graphics::Vertex::Format);
	//
	//mTexturePixelShader.Initialize("../../Assets/Shaders/Texturing.fx");
	//mTextureVertexShader.Initialize("../../Assets/Shaders/Texturing.fx", Vishv::Graphics::VertexPX::Format);
	//
	//mPostProcessingPixelShader.Initialize("../../Assets/Shaders/Merge.fx");
	//mPostProcessingVertexShader.Initialize("../../Assets/Shaders/Merge.fx", Vishv::Graphics::VertexPX::Format);
		
	mRendertarget.Initialize(Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferWidth(),
		Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferHeight(),
		Vishv::Graphics::RenderTarget::Format::RGBA_U8);


	mRendertarget1.Initialize(Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferWidth(),
		Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferHeight(),
		Vishv::Graphics::RenderTarget::Format::RGBA_U8);

	mRendertarget2.Initialize(Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferWidth(),
		Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferHeight(),
		Vishv::Graphics::RenderTarget::Format::RGBA_U8);

	mScreenMesh = Vishv::Graphics::Meshbuilder::CreateNDCQuad();
	mScreenMeshBuffer.Initialize(mScreenMesh);

	mBGColor = Vishv::Graphics::Colors::Gray;

	Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);

	mCylnder = Vishv::Graphics::Meshbuilder::CreateSphereNormal(14, 14, 10.f);
	mDome = Vishv::Graphics::Meshbuilder::CreateSphereUV(14, 14, 500.0f);
	mDomeBuffer.Initialize(mDome);
	mEarth = Vishv::Graphics::Meshbuilder::CreateSphere(512, 512, 10.f);
	//mCylnderBuffer.Initialize(mCylnder);
	mEarthBuffer.Initialize(mEarth);

	mTextureBuffer.Initialize();
	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mOptionsBuffer.Initialize();

	Vishv::Math::Vector3 dir(1.0f, -1.0f, 1.0f);

	mLight.direction = Vishv::Math::Normalize(dir);
	mLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mLight.diffuse = { 0.6f, 0.6f, 0.6f, 1.0f };
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

	//Post processing glow effect
	mGlowScreenMesh = Vishv::Graphics::Meshbuilder::CreateNDCQuad();
	mGlowScreenMeshBuffer.Initialize(mGlowScreenMesh);
	mScreenMeshBuffer.Initialize(mGlowScreenMesh);

	mLighSaber1 = Vishv::Graphics::Meshbuilder::CreateCylinderUV(3, 16, 6.0f, 10.0f);
	mLighSaber2 = Vishv::Graphics::Meshbuilder::CreateCylinderUV(3, 16, 6.0f, 10.0f);

	mSaberPosition1 = { 5.0f, 1.0f, 1.0f };
	mSaberPosition1 = { -5.0f, -1.0f, -1.0f };

	mLighSaberBuffer1.Initialize(mLighSaber1);
	mLighSaberBuffer2.Initialize(mLighSaber2);

	mLightSaberTexture1 = Vishv::Graphics::TextureManager::Get()->LoadTexture("LightsaberTextureBlue.jpg");
	mLightSaberTexture2 = Vishv::Graphics::TextureManager::Get()->LoadTexture("LightsaberTextureRed.jpg");

	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Blur);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Standard);


	//mGlowPixelShader.Initialize("../../Assets/Shaders/Blur.fx");
	//mGlowVertexShader.Initialize("../../Assets/Shaders/Blur.fx", Vishv::Graphics::VertexPX::Format);
	//
	//mMergePixelShader.Initialize("../../Assets/Shaders/Merge.fx");
	//mMergeVertexShader.Initialize("../../Assets/Shaders/Merge.fx", Vishv::Graphics::VertexPX::Format);
}

void GameState::Update()
{
	auto inputSystem = Vishv::Input::InputSystem::Get();
	inputSystem->Update();

	//CameraUpdate(cam);
	//MeshUpdate(mb);


	timmer += deltaTime;
	if (timmer > 720.0f)
		timmer = 0.0f;

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
	//mRendertarget1.BeginRender();
	RenderSceneGlow();
	//render only the glowing objects		in this case the 2 light sabers
	//Vishv::Graphics::SamplerManager::Get()->GetSampler("PointWrap")->BindPS(0);
	MultiGlow();
	//mRendertarget1.EndRender();
	////
	//mRendertarget.BeginRender();
	//RenderScene();
	//mRendertarget.EndRender();
	//
	PostProcess();
}

void GameState::RenderSceneGlow()
{
	//render only the glowing objects		in this case the 2 light sabers
	auto view = scene.sceneCamera->GetViewMatrix();
	auto proj = scene.sceneCamera->GetPerspectiveMatrix();
	auto world = Vishv::Math::Matrix4::TranslateMatrix(mSaberPosition1);

	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Texturing);

	//mTextureVertexShader.Bind();
	//mTexturePixelShader.Bind();


	auto transform = (world * view * proj).Transpose();
	Vishv::Graphics::EffectsManager::Get()->GetBufferData(Vishv::Graphics::EffectType::Texturing)->GetTextureing()->wvp = transform;
	Vishv::Graphics::EffectsManager::Get()->Set(Vishv::Graphics::EffectType::Texturing);
	Vishv::Graphics::EffectsManager::Get()->BindBuffer(Vishv::Graphics::EffectType::Texturing);
	//mTextureBuffer.Set({ transform });
	//mTextureBuffer.BindVS(0);

	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	Vishv::Graphics::TextureManager::Get()->GetTexture(mLightSaberTexture1)->BindPS(0);
	mLighSaberBuffer1.Render();

	world = Vishv::Math::Matrix4::TranslateMatrix(mSaberPosition2);
	transform = (world * view * proj).Transpose();
	Vishv::Graphics::EffectsManager::Get()->GetBufferData(Vishv::Graphics::EffectType::Texturing)->GetTextureing()->wvp = transform;
	Vishv::Graphics::EffectsManager::Get()->Set(Vishv::Graphics::EffectType::Texturing);
	Vishv::Graphics::EffectsManager::Get()->BindBuffer(Vishv::Graphics::EffectType::Texturing);
	//mTextureBuffer.Set({ transform });

	Vishv::Graphics::TextureManager::Get()->GetTexture(mLightSaberTexture2)->BindPS(0);
	mLighSaberBuffer2.Render();

	//apply blur on it 2-5 times
	//mGlowPixelShader.Bind();
	//mGlowVertexShader.Bind();


}

void GameState::MultiGlow()
{
	Vishv::Math::Vector4 kernal;

	kernal.x = 10.0f;
	kernal.y = 25.0f;
	kernal.z = 15.0f;
	kernal.w = 5.0f;

	mOptionsBuffer.Set({ kernal });

	//for (int i = 0; i < mCount; ++i)
	//{
	//	mRendertarget2.BeginRender();
	//	mGlowVertexShader.Bind();
	//	mGlowPixelShader.Bind();
	//	mRendertarget1.BindPS(0);
	//	mOptionsBuffer.BindPS(3);
	//	mOptionsBuffer.BindVS(3);
	//	mGlowScreenMeshBuffer.Render();
	//	mRendertarget2.EndRender();
	//
	//	mRendertarget1.BeginRender();
	//	mGlowVertexShader.Bind();
	//	mGlowPixelShader.Bind();
	//	mRendertarget2.BindPS(0);
	//	mOptionsBuffer.BindPS(3);
	//	mOptionsBuffer.BindVS(3);
	//	mGlowScreenMeshBuffer.Render();
	//	mRendertarget1.EndRender();
	//}
	mRendertarget2.BeginRender();
	
	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Blur);
	//mGlowVertexShader.Bind();
	//mGlowPixelShader.Bind();
	mRendertarget1.BindPS(0);
	mOptionsBuffer.BindPS(3);
	mOptionsBuffer.BindVS(3);
	mGlowScreenMeshBuffer.Render();
	mRendertarget2.EndRender();

}

void GameState::RenderScene()
{
	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Texturing);

	//mTextureVertexShader.Bind();
	//mTexturePixelShader.Bind();

	auto view = scene.sceneCamera->GetViewMatrix();
	auto proj = scene.sceneCamera->GetPerspectiveMatrix();

	auto transform = Vishv::Math::Matrix4::Transpose(Vishv::Math::Matrix4::TranslateMatrix(scene.sceneCamera->GetPosition()) * view * proj);
	mTextureBuffer.Set({ transform });
	mTextureBuffer.BindVS(0);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mDomeTex)->BindPS(0);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	Vishv::Graphics::RasterizerManager::Get()->ChangeState("FrontSolid");
	mDomeBuffer.Render();
	Vishv::Graphics::RasterizerManager::Get()->ChangeState("BackSolid");

	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Standard);

	//mVertexShader.Bind();
	//mPixelShader.Bind();

	auto world = Vishv::Math::Matrix4::TranslateMatrix(mPosition)
		* (Vishv::Math::Matrix4::RotateMatrixX(mRotation.x)
			* Vishv::Math::Matrix4::RotateMatrixY(mRotation.y)
			* Vishv::Math::Matrix4::RotateMatrixZ(mRotation.z));

	TransformData td;
	td.world = world.Transpose();
	td.wvp = (world * view * proj).Transpose();
	td.viewPosition = scene.sceneCamera->GetPosition();

	mTransformBuffer.Set(td);
	mTransformBuffer.BindVS(0);
	mTransformBuffer.BindPS(0);

	mLightBuffer.Set(mLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Set(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	mOptionsBuffer.Set(mOptionsData);
	mOptionsBuffer.BindVS(3);
	mOptionsBuffer.BindPS(3);

	Vishv::Graphics::TextureManager::Get()->GetTexture(mDiffuseMap)->BindPS(0);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mSpecularMap)->BindPS(1);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mDisplacementMap)->BindVS(2);
	Vishv::Graphics::TextureManager::Get()->GetTexture(mNormalMap)->BindPS(3);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	mEarthBuffer.Render();

	//light saber render
	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Texturing);

	//mTextureVertexShader.Bind();
	//mTexturePixelShader.Bind();

	world = Vishv::Math::Matrix4::TranslateMatrix(mSaberPosition1);
	transform = (world * view * proj).Transpose();
	mTextureBuffer.Set({ transform });
	mTextureBuffer.BindVS(0);

	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	Vishv::Graphics::TextureManager::Get()->GetTexture(mLightSaberTexture1)->BindPS(0);
	mLighSaberBuffer1.Render();

	world = Vishv::Math::Matrix4::TranslateMatrix(mSaberPosition2);
	transform = (world * view * proj).Transpose();
	mTextureBuffer.Set({ transform });

	Vishv::Graphics::TextureManager::Get()->GetTexture(mLightSaberTexture2)->BindPS(0);
	mLighSaberBuffer2.Render();
}

void GameState::PostProcess()
{
	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Merge);

	//mPostProcessingPixelShader.Bind();
	//mPostProcessingVertexShader.Bind();

	Vishv::Graphics::SamplerManager::Get()->GetSampler("PointWrap")->BindPS(0);

	//OptionsData od;
	//od.displacement = timmer;
	//od.isNormal = timmer;
	//od.padding[0] = timmer;
	//mOptionsBuffer.Set(od);

	mRendertarget.BindPS(0);
	mRendertarget2.BindPS(1);
	mScreenMeshBuffer.Render();
	//mRendertarget.UnbindPS(0);
	//mRendertarget2.UnbindPS(1);
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
		//bool normal = mOptionsData.isNormal > 0.0f ? true : false;
		Vishv::Graphics::Color bg(mBGColor);
		ImGui::ColorEdit4("BG_Color##Material", &bg.r);
		//ImGui::DragFloat("Displacement##options", &mOptionsData.displacement, 0.01f, 0.0f, 10.0f);
		ImGui::DragInt("Blur Ammount##options", &mCount);
		//ImGui::Checkbox("Normal##options", &normal);
		//mOptionsData.isNormal = normal ? 1.0f : 0.0f;
		//
		if (!(bg == mBGColor))
		{
			mBGColor = bg;
			Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);
		}
	}
	if (ImGui::CollapsingHeader("EarthTransform"))
	{
		ImGui::DragFloat3("Position##Transform", &mPosition.x, 0.1f);
		ImGui::DragFloat3("Rotation##Transform", &mRotation.x, 0.1f);
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
		Vishv::Graphics::SimpleDraw::AddLine(Vishv::Math::Vector3(), { 100.0f, 0.0f, 0.0f }, Vishv::Graphics::Colors::Red);
		Vishv::Graphics::SimpleDraw::AddLine(Vishv::Math::Vector3(), { 0.0f, 100.0f, 0.0f }, Vishv::Graphics::Colors::Green);
		Vishv::Graphics::SimpleDraw::AddLine(Vishv::Math::Vector3(), { 0.0f, 0.0f, 100.0f }, Vishv::Graphics::Colors::Yellow);
	
		Vishv::Graphics::SimpleDraw::AddSphere({ 10.0f, 10.0f, 10.0f }, 50.0f, Vishv::Graphics::Colors::White);

	for (float i = 0; i < 50; ++i)
	{
		Vishv::Graphics::SimpleDraw::AddLine({ i, 0.0f, -50.0f }, { i, 0.0f, 50.0f }, Vishv::Graphics::Colors::DarkGray);
		Vishv::Graphics::SimpleDraw::AddLine({ -50.0f, 0.0f, i }, { 50.0f, 0.0f, i }, Vishv::Graphics::Colors::DarkGray);
	}
	
	Vishv::Graphics::SimpleDraw::Render(*scene.sceneCamera);
}

void GameState::Terminate()
{
	//mTexturePixelShader.Terminate();
	//mTextureVertexShader.Terminate();
	//mVertexShader.Terminate();
	//mPixelShader.Terminate();
	mCylnderBuffer.Terminate();
	mTransformBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTextureBuffer.Terminate();

	//New stuff for post processing
	mRendertarget.Terminate();
	mRendertarget1.Terminate();
	mRendertarget2.Terminate();
	mScreenMeshBuffer.Terminate();
	//mPostProcessingPixelShader.Terminate();
	//mPostProcessingVertexShader.Terminate();

	//mGlowPixelShader.Terminate();
	//mGlowVertexShader.Terminate();
	mGlowScreenMeshBuffer.Terminate();
	//mMergePixelShader.Terminate();
	//mMergeVertexShader.Terminate();
}
