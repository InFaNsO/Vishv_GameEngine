#include "Precompiled.h"
#include "SkyBoxService.h"

#include "GameWorld.h"
#include "CameraService.h"
#include "CameraComponent.h"

#include "Editor.h"

using namespace Vishv;

META_DERIVED_BEGIN(SkyBox, Service)
	META_FIELD_BEGIN
		META_FIELD(mDrawScreenDome, "Show Sky box")
	META_FIELD_END
META_CLASS_END


void Vishv::SkyBox::Initialize()
{
	SetName("Sky Box");

	camSystem = GetWorld().GetService<CameraSystem>();

	mDome.Initialize(Vishv::Graphics::Meshbuilder::CreateSphereUV(12, 12, camSystem->GetMainCamera().Get()->GetComponent<Components::CameraComponent>()->GetCamera().GetFarPlane()));
	mDomeTex = Vishv::Graphics::TextureManager::Get()->LoadTexture("HDRI\\Hanger_Small\\hdr.jpg");
}

void Vishv::SkyBox::Update()
{
	static auto obj = camSystem->GetMainCamera();

	if (!mainCam)
	{
		mainCam = camSystem->GetMainCamera().Get()->GetComponent<Components::CameraComponent>();
	}
	else if (obj != camSystem->GetMainCamera())
	{
		obj = camSystem->GetMainCamera();
		mainCam = obj.Get()->GetComponent<Components::CameraComponent>();
	}
}

void Vishv::SkyBox::DebugUI()
{
	ImGui::Checkbox("Show Sky Box", &mDrawScreenDome);
	if (!mDrawScreenDome && ImGui::CollapsingHeader("Set Background Color"))
	{
		static Vishv::Graphics::Color bgColor = Vishv::Graphics::Colors::Black;
		if (ImGui::ColorEdit4("BackGround Color", &bgColor.r))
		{
			Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(bgColor);
			EditorManager::Get()->SetBackgroundColor(bgColor);
		}
	}
}

void Vishv::SkyBox::Render()
{
	if (!mDrawScreenDome)
		return;

	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Texturing);
	auto view = mainCam->GetCamera().GetViewMatrix();
	auto proj = mainCam->GetCamera().GetPerspectiveMatrix();

	auto transform = Vishv::Math::Matrix4::Transpose(Vishv::Math::Matrix4::TranslateMatrix(mainCam->GetCamera().GetPosition()) * view * proj);

	Vishv::Graphics::EffectsManager::Get()->GetBufferData(Vishv::Graphics::EffectType::Texturing)->GetTextureing()->wvp = transform;
	Vishv::Graphics::EffectsManager::Get()->Set(Vishv::Graphics::EffectType::Texturing);
	Vishv::Graphics::EffectsManager::Get()->BindBuffer(Vishv::Graphics::EffectType::Texturing);

	Vishv::Graphics::TextureManager::Get()->GetTexture(mDomeTex)->BindPS(0);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	Vishv::Graphics::RasterizerManager::Get()->ChangeState("FrontSolid");
	mDome.Render();
	Vishv::Graphics::RasterizerManager::Get()->ChangeState("BackSolid");
}

