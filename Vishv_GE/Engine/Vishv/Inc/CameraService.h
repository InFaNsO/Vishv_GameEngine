 #pragma once
#ifndef INCLUDED_VISHV_CAMERASERVICE_H
#define INCLUDED_VISHV_CAMERASERVICE_H

#include "Service.h"

namespace Vishv::Components
{
	class CameraComponent;
	class TransformComponent;
}
namespace Vishv
{
	class GameObject;
	using GameObjectHandle = Core::Handle<GameObject>;

	class CameraSystem : public Service
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update() override;

		void Register(Components::CameraComponent& cam);
		GameObjectHandle GetMainCamera();

		void SetMainCamera(const GameObjectHandle& cam);
		GameObjectHandle SetMainCamera(int index);

		void TransitionTo(const GameObjectHandle& camHandle, float duration = 2.0f);
		void TransitionTo(int camIndex, float duration = 2.0f);

		void Terminate() override;

		void BindBuffer(const Graphics::EffectType& type);
		Math::Vector2 WorldToScreen(const Math::Vector3& worldCoordinate);
		Math::Vector3 ScreenToWorld(const Math::Vector2& screenCoordinate);
		Math::Vector3 ScreenToWorld(const Math::Vector3& screenCoordinate);
		Physics::Ray MouseToWorldRay();
	
	private:
		int GetIndexFromHandle(const GameObjectHandle& handle);
		void EndTransition();

		int MainCamera = -1;
		Components::TransformComponent* mMainCameraTransformation = nullptr;

		bool isTransitioning = false;
		float transitionDuration = 2.0f;
		float transitionEndTime = 2.0f;
		int transitionCamIndex = -1;
		Components::TransformComponent* TargetCamTransform;

		Math::Vector3 cachePos;
		Math::Quaternion cacheQuat;

		std::vector<Components::CameraComponent*> mCameras;
	};
}


#endif // !INCLUDED_VISHV_CAMERASERVICE_H


