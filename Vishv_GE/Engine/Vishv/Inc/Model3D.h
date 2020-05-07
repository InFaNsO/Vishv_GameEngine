#pragma once
#ifndef INCLUDED_VISHV_COMPONENT_MODEL_3D_H
#define INCLUDED_VISHV_COMPONENT_MODEL_3D_H

#include "Component.h"

namespace Vishv
{
	class CameraSystem;
}

namespace Vishv::Components
{
	class Animation3D;
	class TransformComponent;

	class Model3D : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void DebugUI() override;

		void Render() override;

		void Terminate() override;
		
		void SetModel(Vishv::Graphics::RiggedModel& model);
		void SetModel(std::filesystem::path modelPath, std::string modelName);
		~Model3D();
	
	private:
		friend class Animation3D;
		void SetUpModel();
		void LoadModel();

	private: 
		CameraSystem* mCameraSystem = nullptr;
		Animation3D* myAnimation = nullptr;
		TransformComponent* myTransformation = nullptr;

		std::vector<Math::Matrix4> mTpose;

		bool didNew = false;
		Graphics::RiggedModel* mModel = nullptr;
	};
}

#endif // !INCLUDED_VISHV_COMPONENT_MODEL_3D


