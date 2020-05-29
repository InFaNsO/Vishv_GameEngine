#ifndef INCLUDED_VISHV_SIMPLEDRAW_SERVICE_H
#define INCLUDED_VISHV_SIMPLEDRAW_SERVICE_H

#pragma once
#include "Service.h"

namespace Vishv::Components
{
	class CameraComponent;
}


namespace Vishv
{
	class CameraSystem;

	class SimpleDrawer : public Service
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		bool mDoSimpleDraw = false;

		CameraSystem* camSystem = nullptr;
		Components::CameraComponent* mainCam = nullptr;
	};
}

#endif // !INCLUDED_VISHV_SIMPLEDRAW_SERVICE_H
