#pragma once
#include "Component.h"

namespace Vishv
{
	class CameraService;
}

namespace Vishv::Components
{
	class TransformComponent;

	class CameraComponent : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update() override;
		void SimpleDraw() override;
		void DebugUI() override;
		void Render() override;
		void Terminate() override;

		Math::Vector2 WorldToScreen(const Math::Vector3& worldCoordinate);
		Math::Vector3 ScreenToWorld(const Math::Vector2& screenCoordinate);
		Math::Vector3 ScreenToWorld(const Math::Vector3& screenCoordinate);

		Physics::Ray MouseToWorldRay();

		void BindToBuffer(const Graphics::EffectType& type);

		Graphics::Camera& GetCamera() { return mCamera; }

	private:
		friend class CameraSystem;

		void Calculate();

		bool isMainCamera = false;

		Graphics::Camera mCamera;
		float mNearPlane;
		float mFarPlane;
		float mFeildOfView;
		float mScreenWidth;
		float mScreenHeight;

		Math::Matrix4 mWorldMatrix;
		Math::Matrix4 mWVP;

		TransformComponent* myTransformation = nullptr;
		Math::Transform prvTransform;
	};
}

