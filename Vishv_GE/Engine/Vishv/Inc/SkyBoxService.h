#ifndef INCLUDED_VISHV_SERVICE_SKYBOX_H
#define INCLUDED_VISHV_SERVICE_SKYBOX_H
#pragma once
#include "Service.h"

namespace Vishv::Components
{
	class CameraComponent;
}

namespace Vishv
{
	class CameraSystem;

	class SkyBox : public Service
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update() override;
		void Render() override;
		void DebugUI() override;

	private:
		bool mDrawScreenDome = true;

		CameraSystem* camSystem = nullptr;
		Components::CameraComponent* mainCam = nullptr;

		Vishv::Graphics::MeshBuffer mDome;
		Vishv::Graphics::TextureID mDomeTex;
	};

}



#endif // !INCLUDED_VISHV_SERVICE_SKYBOX_H
