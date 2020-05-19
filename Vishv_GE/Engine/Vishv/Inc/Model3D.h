#pragma once
#ifndef INCLUDED_VISHV_COMPONENT_MODEL_3D_H
#define INCLUDED_VISHV_COMPONENT_MODEL_3D_H

#include "Component.h"

namespace Vishv
{
	class CameraSystem;
	class ModelService;
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
		void SimpleDraw() override;
		void Render() override;

		void Terminate() override;
		
		void SetModel(Vishv::Graphics::RiggedModel& model);
		void SetModel(std::filesystem::path modelPath, std::string modelName);
		~Model3D();
	
	private:
		friend class Animation3D;
		void SetUpModel();
		void LoadModel();

		void GetModelUI();
		void HandleSkeletonUI();

	private:
		class SkeletonUI
		{
		public:
			uint32_t GetDepth();
			void SetBoneDebugColour();
			void ShowBoneHirarchy();
			void SetSkeleton(Vishv::Graphics::Skeleton& skeleton) { mSkeleton = &skeleton; }
			Graphics::Color deepC = Graphics::Colors::LimeGreen;
			Graphics::Color shallowC = Graphics::Colors::OrangeRed;

		private:
			uint32_t getDepth(Vishv::Graphics::Bone* bone);
			void setDebugColor(Vishv::Graphics::Bone* bone, uint32_t currentDepth, uint32_t totalDepth);

			void WriteBoneNameAndCallChildren(Vishv::Graphics::Bone* bone);


			Vishv::Graphics::Skeleton* mSkeleton;
		};

	private: 
		CameraSystem* mCameraSystem = nullptr;
		Animation3D* myAnimation = nullptr;
		TransformComponent* myTransformation = nullptr;

		std::vector<Math::Matrix4> mTpose;

		SkeletonUI mSkelUI;
		ModelService* mModelService = nullptr;

		bool didNew = false;
		bool mShowSkeleton = false;
		Graphics::RiggedModel* mModel = nullptr;
	};
}

#endif // !INCLUDED_VISHV_COMPONENT_MODEL_3D


