#include "Precompiled.h"
#include "GizmoIm.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "CameraService.h"
#include "CameraComponent.h"
#include "TransformComponent.h"


using namespace Vishv;

namespace
{
	std::unique_ptr<ScreenGizmo> sInstance = nullptr;
}

void Vishv::ScreenGizmo::StaticInitialize()
{
	VISHVASSERT(sInstance, "Already initialized");

	sInstance = std::make_unique<ScreenGizmo>();
	sInstance->Initialzie();
}

ScreenGizmo* Vishv::ScreenGizmo::Get()
{
	return sInstance.get();

}

void Vishv::ScreenGizmo::Terminate()
{
}

void Vishv::ScreenGizmo::Initialzie()
{
}

bool Vishv::ScreenGizmo::SetSelectedObject(GameObject* go)
{
	currentObjectTransform = go->GetComponent<Components::TransformComponent>();
	return currentObjectTransform;
}
