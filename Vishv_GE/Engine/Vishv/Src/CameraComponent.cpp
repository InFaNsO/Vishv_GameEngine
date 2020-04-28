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
	Calculate();
}

void Vishv::Components::CameraComponent::Update()
{
	if (prvTransform.mPosition != myTransformation->GetPosition() ||
		prvTransform.GetRotationQuaternion() != myTransformation->Rotation())
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
	mCamera.ComputeMatricies();
	mWorldMatrix = Math::Matrix4::RotateMatrix(myTransformation->Rotation()) * Math::Matrix4::TranslateMatrix(myTransformation->GetPosition());
	mWVP = (mWorldMatrix * mCamera.GetViewMatrix() * mCamera.GetPerspectiveMatrix()).Transpose();
	mWorldMatrix.Transpose();
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
	Math::Vector3 origin = ScreenToWorld(Math::Vector2(static_cast<float>(Input::InputSystem::Get()->GetMouseScreenX()), static_cast<float>(Input::InputSystem::Get()->GetMouseScreenY())));
	return { origin, myTransformation->Forward() };
}

void Vishv::Components::CameraComponent::BindToBuffer(const Graphics::EffectType& type)
{
	auto em = Graphics::EffectsManager::Get();
	auto transformData = em->GetBufferData(type)->GetTransform();

	em->BindBuffer(type);
	transformData->viewPosition = myTransformation->Position();
	transformData->world = mWorldMatrix;
	transformData->wvp = mWVP;
}

