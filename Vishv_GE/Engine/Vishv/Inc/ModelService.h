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

		void Initialize() override;
		void DebugUI() override;

	private:
		friend class Animation3D;
		friend class Model3D;

		void FileParser();
		void SetModel(std::filesystem::path modelPath, std::string modelName);
		void SetupModel();

		void CreateGameObject();

		struct ModelAnimation
		{
			char ModelName[256] = "HolderName";
			Graphics::RiggedModel model;
			Graphics::AnimationSet mAnimations;
		};

		std::vector<ModelAnimation> mModels;
		int selected = 0;
	};
}



