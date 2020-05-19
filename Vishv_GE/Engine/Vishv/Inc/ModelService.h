#pragma once
#include "Service.h"

namespace Vishv::Components
{
	class Animation3D;
	class Model3D;
}

namespace Vishv
{
	class ModelService : public Service
	{
	public:
		META_CLASS_DECLARE

		struct ModelAnimation
		{
			char ModelName[256] = "HolderName";
			Graphics::RiggedModel model;
			Graphics::AnimationSet mAnimations;
		};
	public:
		

		void Initialize() override;
		void DebugUI() override;

		std::vector<ModelAnimation>& GetModels() { return mModels; }



	private:
		friend class Animation3D;

		void FileParser();
		void SetModel(std::filesystem::path modelPath, std::string modelName);
		void SetupModel();

		void CreateGameObject();

		

		std::vector<ModelAnimation> mModels;
		int selected = 0;
	};
}



