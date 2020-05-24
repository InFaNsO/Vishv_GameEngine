#include "Precompiled.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "CameraService.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(CameraComponent, Component)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END

void Vishv::Components::CameraComponent::Initialize()
{
	myTransformation = GetOwner().GetComponent<TransformComponent>();
	VISHVASSERT(myTransformation, "No Transform component found");
	mCamera.transform = &myTransformation->Transform();
	Calculate();
}

void Vishv::Components::CameraComponent::Update()
{
	if (prvTransform.mPosition != myTransformation->GetPosition() ||
		prvTransform.Rotation() != myTransformation->Rotation())
	{
		Calculate();
	}
}

void Vishv::Components::CameraComponent::SimpleDraw()
{
}

void Vishv::Components::CameraComponent::DebugUI()
{
}

void Vishv::Components::CameraComponent::Render()
{
}

void Vishv::Components::CameraComponent::Terminate()
{
}

void Vishv::Components::CameraComponent::Calculate()
{
	//update prvTransform
	prvTransform.mPosition = myTransformation->Position();
	prvTransform.SetRotation(myTransformation->Rotation());

	//Calculate new Matrix
	mCamera.ComputeMatricies(aspectRatio);
	//mWorldMatrix = Math::Matrix4::RotateMatrix(myTransformation->Rotation()) * Math::Matrix4::TranslateMatrix(myTransformation->GetPosition());
	//mWVP = (mWorldMatrix * mCamera.GetViewMatrix() * mCamera.GetPerspectiveMatrix()).Transpose();
	//mWorldMatrix.Transpose();
}

Math::Matrix4 Vishv::Components::CameraComponent::ViewMatrix()
{
	return mCamera.GetViewMatrix();
}
Math::Matrix4 Vishv::Components::CameraComponent::ProjectionMatrix()
{
	return mCamera.GetPerspectiveMatrix();
}

Math::Vector2 Vishv::Components::CameraComponent::WorldToScreen(const Math::Vector3& worldCoordinate)
{
	Math::Vector3 uv = mWVP * worldCoordinate;
	return Math::Vector2(uv.x, uv.y);
}

Math::Vector3 Vishv::Components::CameraComponent::ScreenToWorld(const Math::Vector2& screenCoordinate)
{
	return ScreenToWorld({ screenCoordinate.x, screenCoordinate.y, 0.0f });
}

Math::Vector3 Vishv::Components::CameraComponent::ScreenToWorld(const Math::Vector3& screenCoordinate)
{
	Math::Vector3 worldPos = mWVP.Inverse() * screenCoordinate;

	return std::move(worldPos);
}

Physics::Ray Vishv::Components::CameraComponent::MouseToWorldRay()
{
	Math::Vector2 mousePos = { ImGui::GetMousePos().x, ImGui::GetMousePos().y };

	Math::Vector3 origin = ScreenToWorld(Math::Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
	return { origin, myTransformation->Forward() };
}

void Vishv::Components::CameraComponent::BindToBuffer(const Graphics::EffectType& type, const Math::Transform& objTransform)
{
	auto em = Graphics::EffectsManager::Get();
	auto transformData = em->GetBufferData(type)->GetTransform();

	auto holder = objTransform.GetTransformMatrix();
	mWorldMatrix = holder;//Math::Matrix4::RotateMatrix(objTransform.Rotation()) * Math::Matrix4::TranslateMatrix(objTransform.Position()); //objTransform.GetTransformMatrix();
	mWVP = (mWorldMatrix * mCamera.GetViewMatrix() * mCamera.GetPerspectiveMatrix()).Transpose();
	mWorldMatrix.Transpose();

	transformData->viewPosition = myTransformation->Position();
	transformData->world = mWorldMatrix;
	transformData->wvp = mWVP;
}

