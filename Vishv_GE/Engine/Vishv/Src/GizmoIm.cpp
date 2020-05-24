#include "Precompiled.h"
#include "GizmoIm.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "CameraService.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

#include "ImGuizmo.h"

using namespace Vishv;

namespace
{
	std::unique_ptr<Editor::ScreenGizmo> sInstance = nullptr;
}

void Vishv::Editor::ScreenGizmo::StaticInitialize()
{
	//VISHVASSERT(sInstance, "Already initialized");

	sInstance = std::make_unique<Editor::ScreenGizmo>();
	sInstance->Initialzie();
}

Editor::ScreenGizmo* Vishv::Editor::ScreenGizmo::Get()
{
	return sInstance.get();

}

void Vishv::Editor::ScreenGizmo::Update()
{
	//ImGuizmo::SetOrthographic(false);
	//ImGuizmo::BeginFrame();

	//ImGuizmo::OPERATION mode = ImGuizmo::OPERATION::TRANSLATE;

	//switch (mMode)
	//{
	//case GizmoMode::Translate:
	//	mode = ImGuizmo::OPERATION::TRANSLATE;
	//case GizmoMode::Rotate:
	//	mode = ImGuizmo::OPERATION::ROTATE;
	//case GizmoMode::Scale:
	//	mode = ImGuizmo::OPERATION::SCALE;
	//}

	auto Mat = currentObjectTransform->GetTransformMatrix();

	auto& cam = CamService->GetMainCamera().Get()->GetComponent<Components::CameraComponent>()->GetCamera();
	//ImGuizmo::Manipulate(cam.GetViewMatrix().v.data(), cam.GetPerspectiveMatrix().v.data(), mode, ImGuizmo::MODE::WORLD,
	//	Mat.v.data());

	currentObjectTransform->SetTransformation(Mat);
	auto mat = cam.GetViewMatrix();
	//ImGuizmo::ViewManipulate(mat.v.data(), 8.f, ImVec2(0.0f, 0.0f), ImVec2(128, 128), 0x10101010);
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
