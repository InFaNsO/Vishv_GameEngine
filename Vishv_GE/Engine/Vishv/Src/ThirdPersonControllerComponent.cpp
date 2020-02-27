#include "Precompiled.h"
#include "ThirdPersonControllerComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameWorld.h"

META_DERIVED_BEGIN(Vishv::Components::ThirdPersonControllerComponent, Vishv::Components::Component)
	META_FIELD_BEGIN
		META_FIELD(mLookSencivity, "LookSencivity")
		META_FIELD(mMoveSpeed, "MoveSpeed")
	META_FIELD_END
META_CLASS_END


namespace
{
	bool customCompare(const Vishv::Math::Vector3& a, const Vishv::Math::Vector3& b, int order = 1000)
	{
		int ax = (int)(a.x * order);
		int ay = (int)(a.y * order);
		int az = (int)(a.z * order);

		int bx = (int)(b.x * order);
		int by = (int)(b.y * order);
		int bz = (int)(b.z * order);

		return ax == bx && ay == by && az == bz;
	}
}

void Vishv::Components::ThirdPersonControllerComponent::Initialize()
{
	mCamera = GetOwner().GetWorld().GetMainCamera();
	mTransformComponent = GetOwner().GetComponent<Vishv::Components::TransformComponent>();

	offsetCamera = { 0.0f, 250.0f, -200.0f };
}

void Vishv::Components::ThirdPersonControllerComponent::Update(float deltaTime)
{
	auto input = Vishv::Input::InputSystem::Get();

	if (input->IsKeyDown(Input::KeyCode::W) && input->IsKeyDown(Input::KeyCode::LSHIFT) || mForward && mBoost)
	{
		mTransformComponent->TranslateForward(mMoveSpeed * deltaTime);
		mForward = false;
	}
	else if (input->IsKeyDown(Input::KeyCode::W) || mForward)
	{
		mTransformComponent->TranslateForward(mMoveSpeed * deltaTime);
		mForward = false;
	}


	if (input->IsKeyDown(Input::KeyCode::S) && input->IsKeyDown(Input::KeyCode::LSHIFT) || mBackward && mBoost)
	{
		mTransformComponent->TranslateForward(-mMoveSpeed * deltaTime);
		mBackward = false;
	}
	else if (input->IsKeyDown(Input::KeyCode::S) || mBackward)
	{
		mTransformComponent->TranslateForward(-mMoveSpeed * deltaTime);
		mBackward = false;
	}

	if (input->IsKeyDown(Input::KeyCode::Q))
	{
		mTransformComponent->RotateUp(-60.0f * deltaTime);
		float angle = Vishv::Math::GetAngle(Math::Normalize((mTransformComponent->Position() - mCamera->transform.Position())), mCamera->transform.Forward());
		mCamera->transform.RotateY(-angle * Math::Constans::RadToDeg * deltaTime);
	}
	else if (input->IsKeyDown(Input::KeyCode::E))
	{
		mTransformComponent->RotateUp(60.0f * deltaTime);
		float angle = Vishv::Math::GetAngle(Math::Normalize((mTransformComponent->Position() - mCamera->transform.Position())), mCamera->transform.Forward());
		mCamera->transform.RotateY(angle * Math::Constans::RadToDeg * deltaTime);
		//mCamera->transform.RotateY(-60.0f * deltaTime);
	}

	//update position
	Math::Vector3 upRot = { 0.0f, offsetCamera.y, 0.0f };
	mCamera->transform.mPosition = mTransformComponent->Position() + upRot + (mTransformComponent->Forward() * offsetCamera.z);


	if (!input->IsKeyDown(Input::KeyCode::TAB))
		return;

	int lr = input->GetMouseMoveX();
	int ud = input->GetMouseMoveY();

	auto upP = mTransformComponent->Up();
	upP = -upP;

	if (lr != 0)
		prvLr = lr;

	mTransformComponent->Rotate(upP, lr * mLookSencivity);

	float angle = Vishv::Math::GetAngle(Math::Normalize((mTransformComponent->Position() - mCamera->transform.Position())), mCamera->transform.Forward());

	auto forwardPlayer = mTransformComponent->Forward();
	auto forwardCam = mCamera->transform.Forward();

	if (angle)//(!customCompare(mCamera->transform.Forward(), mTransformComponent->Forward(), 10))
	{
		float deg = angle * Math::Constans::RadToDeg;

		if (Math::Abs(deg  - prvDeg) < 0.01f)
			return;

		prvDeg = deg;

		if (prvLr > 0)
			deg *= -1;
		//if (forwardPlayer.x < forwardCam.x && forwardPlayer.y > 0.0f)
		//	deg *= -1.0f;
		//else if (forwardPlayer.x > forwardCam.x && forwardPlayer.y < 0.0f)
		//	deg *= -1.0f;

		mCamera->transform.RotateY(deg * deltaTime);
		//mCamera->transform.RotateX(-ud);
		//mCamera->LookAt(mTransformComponent->Position() + upRot);
	}
}

void Vishv::Components::ThirdPersonControllerComponent::DebugUI()
{
}



