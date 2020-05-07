#include "Precompiled.h"
#include "Model3D.h"

#include "Animation3D.h"
#include "TransformComponent.h"

#include "GameWorld.h"
#include "CameraService.h"
#include "CameraComponent.h"
#include "imfilebrowser.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(Model3D, Component)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END

namespace
{
	std::unique_ptr<ImGui::FileBrowser> modelImporterFileBrowser = nullptr;
	static std::filesystem::path fileexe = "..\\..\\Debug\\ModelImporter.exe";
}
namespace
{
	using namespace Vishv::Graphics;

	void UpdateTransformMatrixFunc(const Bone* bone, std::vector<Vishv::Math::Matrix4>& boneMatrix, const std::vector<Vishv::Math::Matrix4>& animate)
	{
		if (bone->parent)
			boneMatrix[bone->index] = ((animate[bone->index])) * boneMatrix[bone->parentId];
		else
			boneMatrix[bone->index] = (animate[bone->index]);// *bone->toParentTransform;

		for (auto child : bone->children)
			UpdateTransformMatrixFunc(child, boneMatrix, animate);
	}
}


void Model3D::Initialize()
{
	myTransformation = GetOwner().GetComponent<TransformComponent>();
	mCameraSystem = GetOwner().GetWorld().GetService<CameraSystem>();

	//setup file browser
	modelImporterFileBrowser = std::make_unique<ImGui::FileBrowser>(ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_EnterNewFilename);
	modelImporterFileBrowser->SetTitle("Model Import");
	modelImporterFileBrowser->SetPwd(Graphics::TextureManager::Get()->GetRootPath());
	modelImporterFileBrowser->SetTypeFilters({ ".vmesh" });
}

 
void Vishv::Components::Model3D::Terminate()
{
	if (didNew)
		delete mModel;

	mModel = nullptr;
}

void Vishv::Components::Model3D::DebugUI()
{
	if (mModel == nullptr)
	{
		if (ImGui::Button("Load Model"))
		{
			modelImporterFileBrowser->Open();
		}

		modelImporterFileBrowser->Display();
		LoadModel();
	}
}

void Vishv::Components::Model3D::LoadModel()
{
	if (!modelImporterFileBrowser->HasSelected())
		return;
	auto path = modelImporterFileBrowser->GetSelected();
	if (!path.has_extension())
	{
		modelImporterFileBrowser->ClearSelected();
		return;
	}
	auto ext = path.extension();
	if (path.extension() != ".vmesh")
		return;

	modelImporterFileBrowser->ClearSelected();
	modelImporterFileBrowser->Close();

	std::string name = path.filename().string();
	size_t pos = name.find(path.filename().extension().string());

	name.erase(pos, path.filename().extension().string().length());

	SetModel(path.parent_path(), name);
}

Vishv::Components::Model3D::~Model3D()
{
	VISHVASSERT(!mModel, "[Model 3D] Terminate not called on the component, int object %s", GetOwner().GetName());
}

void Vishv::Components::Model3D::SetModel(Vishv::Graphics::RiggedModel& model)
{
	mModel = &model;
	mTpose.resize(mModel->skeleton.bones.size());
	UpdateTransformMatrixFunc(mModel->skeleton.root, mTpose, mModel->mTPosToParent);
}

void Vishv::Components::Model3D::SetModel(std::filesystem::path modelPath, std::string modelName)
{
	mModel = new Graphics::RiggedModel;
	didNew = true;

	using namespace Graphics;

	//model load and import
	MeshIO mio;
	mio.LoadMeshGeneral(modelPath / (modelName + ".vmesh"));
	mio.GetModel(mModel->model);

	auto textureManager = Vishv::Graphics::TextureManager::Get();
	for (uint32_t i = 0; i < mModel->model.mMaterials.size(); ++i)
	{
		auto& material = mModel->model.mMaterials[i];
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
	for (uint32_t i = 0; i < mModel->model.mMeshes.size(); ++i)
	{
		mModel->model.mMeshes[i].mBuffer.Initialize(mModel->model.mMeshes[i].mMesh);
	}

	//skeleton Import
	Vishv::Graphics::SkeletonIO skelIO;
	skelIO.LoadSkeleton(modelPath / (modelName + ".vskel"), mModel->skeleton);

	SetUpModel();
}



void Vishv::Components::Model3D::SetUpModel()
{
	mModel->mTPosToParent.reserve(mModel->skeleton.bones.size());
	mTpose.resize(mModel->skeleton.bones.size());
	
	for (auto& bone : mModel->skeleton.bones)
		mModel->mTPosToParent.emplace_back(bone->toParentTransform);

	UpdateTransformMatrixFunc(mModel->skeleton.root, mTpose, mModel->mTPosToParent);
}



void Vishv::Components::Model3D::Render()
{
	if (!mModel)
		return;

	auto em = Graphics::EffectsManager::Get();
	auto type = Graphics::EffectType::Skinning;

	em->BindEffect(type);
	mCameraSystem->BindBuffer(type, myTransformation->Transform());

	if (myAnimation)
	{
		myAnimation->BindBonesToBuffer();
	}
	else
	{
		for (size_t i = 0; i < mModel->skeleton.GetBoneArray().size() && i < (size_t)mModel->skeleton.MaxBoneCount(); ++i)
			em->GetBufferData(type)->GetBonetransformData()->boneTransforms[i] = 
			(mModel->skeleton.bones[i]->offsetTransform * 
				mTpose[i]).Transpose();	//multipy bone transformation aswell
	}
	em->Set(type);
	em->BindBuffer(type);

	mModel->model.Render();
}
