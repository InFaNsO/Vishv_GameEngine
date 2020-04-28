#ifndef INCLUDED_VISHV_COMPONENTS_THIRD_PERSON_CONTROLLER_H
#define INCLUDED_VISHV_COMPONENTS_THIRD_PERSON_CONTROLLER_H

#include "Component.h"
namespace Vishv
{
	class CameraSystem;
}

namespace Vishv::Components
{
	class TransformComponent;

	class ThirdPersonControllerComponent : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update() override;
		void DebugUI() override;

	private:
		CameraSystem* mCamSys;
		TransformComponent* mTransformComponent;

		Vishv::Graphics::Camera* mCamera;
		Vishv::Math::Vector3 offsetCamera;

		float mLookSencivity = 0.30f;
		float mMoveSpeed = 100.0f;
		float mBoostIncrement = 1.5f;

		bool mForward	= false;
		bool mBackward	= false;
		bool mBoost		= false;
		bool mCrouch	= false;

		bool mTurnLeft	= false;
		bool mTurnRight	= false;
		
		float prvDeg = 0.0f;
		int prvLr;
	};
}

#endif // !INCLUDED_VISHV_COMPONENTS_THIRD_PERSON_CONTROLLER_H



