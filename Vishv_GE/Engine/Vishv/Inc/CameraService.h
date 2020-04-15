#pragma once
#ifndef INCLUDED_VISHV_CAMERASERVICE_H
#define INCLUDED_VISHV_CAMERASERVICE_H

#include "Service.h"

namespace Vishv
{
	class CameraSystem : public Service
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void DebugUI() override;

		void Update(float deltaTime) override;


		Graphics::Camera* GetCamera(std::string& name);
		Graphics::Camera* AddCamera(std::string name);

		Graphics::Camera* GetMainCamera();
		Graphics::Camera* SetMainCamera(std::string& name);

		void Terminate() override;

	private:
		int MainCamera = -1;

		std::vector<std::string> mNames;
		std::vector<Graphics::Camera> mCameras;

	};
}


#endif // !INCLUDED_VISHV_CAMERASERVICE_H


