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
	std::unique_ptr<Editor::ScreenGizmo> sInstance = nullptr;
}

void Vishv::Editor::ScreenGizmo::StaticInitialize()
{
	VISHVASSERT(sInstance, "Already initialized");

	sInstance = std::make_unique<Editor::ScreenGizmo>();
	sInstance->Initialzie();
}

Editor::ScreenGizmo* Vishv::Editor::ScreenGizmo::Get()
{
	return sInstance.get();

}

void Vishv::Editor::ScreenGizmo::Terminate()
{
}

void Vishv::Editor::ScreenGizmo::Initialzie()
{
}

bool Vishv::Editor::ScreenGizmo::SetSelectedObject(GameObject* go)
{
	currentObjectTransform = go->GetComponent<Components::TransformComponent>();
	return currentObjectTransform;
}
