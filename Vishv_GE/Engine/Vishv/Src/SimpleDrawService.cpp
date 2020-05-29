#include "Precompiled.h"
#include "SimpleDrawService.h"

#include "GameWorld.h"
#include "CameraComponent.h"
#include "CameraService.h"


using namespace Vishv;

META_DERIVED_BEGIN(SimpleDrawer, Service)
	META_FIELD_BEGIN
		META_FIELD(mDoSimpleDraw, "DoSimpleDraw")
	META_FIELD_END
META_CLASS_END


void Vishv::SimpleDrawer::Initialize()
{
	SetName("Simple Drawer");
	camSystem = GetWorld().GetService<CameraSystem>();
}

void Vishv::SimpleDrawer::Update()
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


void Vishv::SimpleDrawer::Render()
{
	if (mDoSimpleDraw)
		Graphics::SimpleDraw::Render(mainCam->GetCamera());
}



