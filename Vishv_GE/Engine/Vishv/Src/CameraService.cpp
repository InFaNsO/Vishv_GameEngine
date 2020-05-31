#include "Precompiled.h"
#include "CameraService.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "GameWorld.h"

using namespace Vishv;

META_DERIVED_BEGIN(CameraSystem, Service)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END

void Vishv::CameraSystem::Initialize()
{
	SetName("Camera System");

	mCameras.reserve(10);
	GameObject mainCam;
	mainCam.SetName("MainCamera");
	auto cam = GetWorld().RegisterGameObject(std::move(mainCam));
	cam.Get()->AddComponent<Components::TransformComponent>();
	cam.Get()->AddComponent<Components::CameraComponent>();
	cam.Get()->Initialize();

	auto added = Register(cam);
	VISHVASSERT(added, "[Camera System] Unable to add main camera");
}

void Vishv::CameraSystem::Update()
{
	//update the current camera;
	if (MainCamera < 0)
		return;

	mCameras[MainCamera]->Update();
	
	if (!isTransitioning)
		return;

	auto t = Core::Time::Get();

	if (t->CurrentTime() < transitionEndTime)
	{
		//do lerping
		float percent = t->CurrentTime() / transitionEndTime;
		mMainCameraTransformation->GetPosition() = Math::Vector3::Lerp(cachePos, TargetCamTransform->Position(), percent);
		mMainCameraTransformation->SetRotation(Math::Quaternion::Slerp(cacheQuat, TargetCamTransform->Rotation(), percent));
	}
	else
	{
		//end transition
		int index = transitionCamIndex;
		EndTransition();
		SetMainCamera(index);
	}
	
}

void Vishv::CameraSystem::SetWidthNHeight(float width, float height)
{ 
	mCameras[MainCamera]->aspectRatio = width / height; 
}

void Vishv::CameraSystem::BindBuffer(const Graphics::EffectType& type, const Math::Transform& objTransform)
{
	mCameras[MainCamera]->BindToBuffer(type, objTransform);
}
Math::Vector2 Vishv::CameraSystem::WorldToScreen(const Math::Vector3& worldCoordinate)
{
	return mCameras[MainCamera]->WorldToScreen(worldCoordinate);
}
Math::Vector3 Vishv::CameraSystem::ScreenToWorld(const Math::Vector2& screenCoordinate)
{
	return mCameras[MainCamera]->ScreenToWorld(screenCoordinate);
}

Math::Vector3 Vishv::CameraSystem::ScreenToWorld(const Math::Vector3& screenCoordinate)
{
	return mCameras[MainCamera]->ScreenToWorld(screenCoordinate);
}
Physics::Ray Vishv::CameraSystem::MouseToWorldRay()
{
	return mCameras[MainCamera]->MouseToWorldRay();
}

GameObjectHandle Vishv::CameraSystem::GetMainCamera()
{
	if (MainCamera == -1)
		return GameObjectHandle();

	return mCameras[MainCamera]->GetOwner().GetHandle();
}

void Vishv::CameraSystem::SetMainCamera(const GameObjectHandle& cam)
{
	VISHVASSERT(cam.Get()->GetComponent<Components::CameraComponent>(), "[CameraSystem] game object doesnt have a camera");

	int index = 0;
	bool found = false;
	for (auto& camera : mCameras)
	{
		if (camera->GetOwner().GetHandle() == cam)
		{
			mCameras[MainCamera]->isMainCamera = false;
			MainCamera = index;
			mCameras[MainCamera]->isMainCamera = true;

			found = true;
			break;
		}
		++index;
	}

	if (!found)
	{
		//add camera
	}
}

void Vishv::CameraSystem::TransitionTo(const GameObjectHandle& camHandle, float duration)
{
	TransitionTo(GetIndexFromHandle(camHandle), duration);
}

void Vishv::CameraSystem::TransitionTo(int camIndex, float duration)
{
	VISHVASSERT(camIndex >= 0, "[Camera System] invalid index used");
	VISHVASSERT(MainCamera != camIndex, "[Camera System] invalid transition");

	auto t = Core::Time::Get();

	if (isTransitioning)
		EndTransition();

	isTransitioning = true;
	transitionCamIndex = camIndex;
	transitionDuration = duration;
	transitionEndTime = t->CurrentTime() + duration;
	TargetCamTransform = mCameras[transitionCamIndex]->GetOwner().GetComponent<Components::TransformComponent>();

	cachePos = mMainCameraTransformation->GetPosition();
	cacheQuat = mMainCameraTransformation->Rotation();
}

GameObjectHandle Vishv::CameraSystem::SetMainCamera(int index)
{
	VISHVASSERT(mCameras.size() != 0, "[Camera System] No Cameras added to the system");
	VISHVASSERT(static_cast<size_t>(index) < mCameras.size(), "[Camera System] Invalid camera index");

	if (MainCamera >= 0)
	{
		mCameras[MainCamera]->isMainCamera = false;
	}
	MainCamera = index;
	mCameras[MainCamera]->isMainCamera = true;

	mMainCameraTransformation = mCameras[MainCamera]->GetOwner().GetComponent<Components::TransformComponent>();

	return mCameras[MainCamera]->GetOwner().GetHandle();
}

void Vishv::CameraSystem::Terminate()
{
	mCameras.clear();
}

bool Vishv::CameraSystem::Register(GameObjectHandle cam)
{
	auto comp = cam.Get()->GetComponent<Components::CameraComponent>();
	if (!comp)
		return false;
	
	Register(*comp);
	return true;
}


void Vishv::CameraSystem::Register(Components::CameraComponent& cam)
{
	mCameras.emplace_back(&cam);
	if (MainCamera == -1)
		SetMainCamera(0);
}

int Vishv::CameraSystem::GetIndexFromHandle(const GameObjectHandle& handle)
{
	VISHVASSERT(handle.Get()->GetComponent<Components::CameraComponent>(), "[CameraSystem] game object doesnt have a camera");

	int index = 0;
	bool found = false;
	for (auto& camera : mCameras)
	{
		if (camera->GetOwner().GetHandle() == handle)
		{
			mCameras[MainCamera]->isMainCamera = false;
			MainCamera = index;
			mCameras[MainCamera]->isMainCamera = true;

			found = true;
			break;
		}
		++index;
	}

	VISHVASSERT(found, "[CameraSystem] the game object does not belong to the system");

	return index;
}

void Vishv::CameraSystem::EndTransition()
{
	isTransitioning = false;
	transitionDuration = 0.f;
	transitionEndTime = 0.f;
	transitionCamIndex = -1;
	TargetCamTransform = nullptr;
	mMainCameraTransformation->GetPosition() = cachePos;
	mMainCameraTransformation->SetRotation(std::move(cacheQuat));

	cachePos = Math::Vector3();
	cacheQuat = Math::Quaternion::CreateIdentity();
}

