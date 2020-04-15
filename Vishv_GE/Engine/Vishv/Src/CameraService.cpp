#include "Precompiled.h"
#include "CameraService.h"

using namespace Vishv;

META_DERIVED_BEGIN(CameraSystem, Service)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END

void Vishv::CameraSystem::Initialize()
{
	mNames.reserve(10);
	mCameras.reserve(10);
}

void Vishv::CameraSystem::Update(float deltaTime)
{
	for (auto& cam : mCameras)
	{
		cam.ComputeMatricies();
	}
}

void Vishv::CameraSystem::DebugUI()
{
	int count = 0;
	for (auto& name : mNames)
	{
		ImGui::CollapsingHeader(name.c_str());
	}

	if (ImGui::Button("Add Camera"))
	{
		AddCamera("New Cam " + count);
	}
}

Graphics::Camera* Vishv::CameraSystem::GetCamera(std::string& name)
{
	int ind = 0;
	for (auto& n : mNames)
	{
		if (n == name)
			return &mCameras[ind];
		ind++;
	}

	return nullptr;
}

Graphics::Camera* Vishv::CameraSystem::AddCamera(std::string name)
{
	if (auto cam = GetCamera(name); cam != nullptr)
	{
		return cam;
	}

	mNames.emplace_back(std::move(name));
	return &mCameras.emplace_back(Graphics::Camera());
}

Graphics::Camera* Vishv::CameraSystem::GetMainCamera()
{
	if (MainCamera == -1)
		return nullptr;

	return &mCameras[MainCamera];
}

Graphics::Camera* Vishv::CameraSystem::SetMainCamera(std::string& name)
{
	int ind = 0;
	for (auto& n : mNames)
	{
		if (n == name)
		{
			MainCamera = ind;
			return &mCameras[MainCamera];
		}
		ind++;
	}

	return AddCamera(std::move(name));
}


void Vishv::CameraSystem::Terminate()
{
	mNames.clear();
	mCameras.clear();
}


