#include "Precompiled.h"
#include "ModelService.h"

#include "Animation3D.h"
#include "Model3D.h"
#include "TransformComponent.h"

#include "GameWorld.h"

#include "imfilebrowser.h"

using namespace Vishv;

META_DERIVED_BEGIN(ModelService, Service)
	META_NO_FIELD
META_CLASS_END


namespace
{
	std::unique_ptr<ImGui::FileBrowser> modelImporter = nullptr;
}

void Vishv::ModelService::Initialize()
{
	mModels.reserve(10);
	SetName("ModelService");

	//setup file browser
	modelImporter = std::make_unique<ImGui::FileBrowser>(ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_EnterNewFilename);
	modelImporter->SetTitle("Model & Import");
	modelImporter->SetPwd(Graphics::TextureManager::Get()->GetRootPath());
	modelImporter->SetTypeFilters({ ".vanim", ".vmesh" });
}

void Vishv::ModelService::DebugUI()
{
	if (ImGui::Button("Add New"))
	{
		AddNew();
	}

	for (size_t i = 0; i < mModels.size(); ++i)
	{
		std::string inputLable = "Name##" + std::to_string(i);
		ImGui::InputText(inputLable.c_str(), &mModels[i].ModelName[0], 256);
		if (!ImGui::CollapsingHeader(mModels[i].ModelName))
			continue;

		std::string name = "Load##" + std::to_string(i);
		if (ImGui::Button(name.c_str()))
		{
			modelImporter->Open();
			selected = static_cast<int>(i);
		}

		if (mModels[i].model.model.mMeshes.size() > 0 && mModels[i].mAnimations.animationClips.size() > 0)
		{
			if (ImGui::Button("Create GameObject"))
			{
				selected = static_cast<int>(i);
				CreateGameObject();
			}
		}

		std::string blendLable = "Blending Time##" + std::to_string(i);
		ImGui::DragFloat(blendLable.c_str(), &mModels[i].mAnimations.blendTimer);
		for (size_t j = 0; j < mModels[i].mAnimations.animationClips.size(); ++j)
		{
			auto clip = mModels[i].mAnimations.animationClips[j].get();
			if (!ImGui::CollapsingHeader(clip->name.c_str()))
				continue;
			std::string loopingText = "Is Looping##" + std::to_string(i * 100 +j);
			if (ImGui::Checkbox(loopingText.c_str(), &clip->isLooping))
			{
				//for (size_t i = 0; i < clip->boneAnimations.size(); ++i)
				//	clip->boneAnimations[i]->animation.SetLooping(clip->isLooping);
			}
			ImGui::Text("Duration: %f", clip->duration);
			ImGui::Text("Ticks Per Second: %f", clip->ticksPerSecond);
		}
	}
	modelImporter->Display();
	FileParser();
}

void Vishv::ModelService::AddNew()
{
	mModels.push_back(ModelAnimation());
	selected = static_cast<int>(mModels.size()) - 1;
}

void Vishv::ModelService::FileParser()
{
	if (!modelImporter->HasSelected())
		return;
	auto path = modelImporter->GetSelected();
	Load(std::move(path));
}

void Vishv::ModelService::Load(std::filesystem::path&& path)
{
	if (!path.has_extension())
	{
		modelImporter->ClearSelected();
		return;
	}
	auto ext = path.extension();
	if (path.extension() == ".vmesh")
	{
		std::string name = path.filename().string();
		size_t pos = name.find(path.filename().extension().string());

		name.erase(pos, path.filename().extension().string().length());
		SetModel(path.parent_path(), name);
	}
	else if (path.extension() == ".vanim")
	{
		mModels[selected].mAnimations.animationClips.push_back(std::make_unique<Vishv::Graphics::AnimationClip>());
		Vishv::Graphics::AnimationIO aio;
		aio.LoadAnimation(path, *mModels[selected].mAnimations.animationClips.back());
	}
	modelImporter->ClearSelected();
	modelImporter->Close();
}



void Vishv::ModelService::SetModel(std::filesystem::path modelPath, std::string modelName)
{
	using namespace Graphics;

	*mModels[selected].ModelName = *modelName.c_str();
	auto& mod = mModels[selected].model;

	//model load and import
	MeshIO mio;
	mio.LoadMeshGeneral(modelPath / (modelName + ".vmesh"));
	mio.GetModel(mod.model);

	auto textureManager = Vishv::Graphics::TextureManager::Get();
	for (uint32_t i = 0; i < mod.model.mMaterials.size(); ++i)
	{
		auto& material = mod.model.mMaterials[i];
		if (material.diffuseName != "empty")
			material.diffuseID = textureManager->LoadTexture(material.diffuseName, false);
		else
			material.diffuseID = textureManager->LoadTexture("black.jpg");
		if (material.bumpName != "empty")
			material.bumpID = textureManager->LoadTexture(material.bumpName, false);
		else
			material.bumpID = textureManager->LoadTexture("black.jpg");
		if (material.normalName != "empty")
			material.normalID = textureManager->LoadTexture(material.normalName, false);
		else
			material.normalID = textureManager->LoadTexture("black.jpg");
		if (material.specularName != "empty")
			material.specularID = textureManager->LoadTexture(material.specularName, false);
		else
			material.specularID = textureManager->LoadTexture("black.jpg");
	}
	for (uint32_t i = 0; i < mod.model.mMeshes.size(); ++i)
	{
		mod.model.mMeshes[i].mBuffer.Initialize(mod.model.mMeshes[i].mMesh);
	}

	//skeleton Import
	Vishv::Graphics::SkeletonIO skelIO;
	skelIO.LoadSkeleton(modelPath / (modelName + ".vskel"), mod.skeleton);

	SetupModel();
}

void Vishv::ModelService::SetupModel()
{
	mModels[selected].model.mTPosToParent.reserve(mModels[selected].model.skeleton.bones.size());

	for (auto& bone : mModels[selected].model.skeleton.bones)
		mModels[selected].model.mTPosToParent.emplace_back(bone->toParentTransform);
}

void Vishv::ModelService::CreateGameObject()
{
	GameObject go;
	go.SetName(mModels[selected].ModelName);
	auto model = GetWorld().RegisterGameObject(std::move(go));

	model.Get()->AddComponent<Components::TransformComponent>();
	auto mod = model.Get()->AddComponent<Components::Model3D>();
	mod->Initialize();
	mod->SetModel(mModels[selected].model);
	auto anim = model.Get()->AddComponent<Components::Animation3D>();
	anim->Initialize();
	anim->SetAnimations(mModels[selected].mAnimations);
}

