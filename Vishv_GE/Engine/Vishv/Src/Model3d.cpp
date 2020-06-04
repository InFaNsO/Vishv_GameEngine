#include "Precompiled.h"
#include "Model3D.h"

#include "Animation3D.h"
#include "TransformComponent.h"
#include "PostProcessor.h"

#include "GameWorld.h"
#include "CameraService.h"
#include "CameraComponent.h"
#include "imfilebrowser.h"
#include "ModelService.h"

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
	mModelService = GetOwner().GetWorld().GetService<ModelService>();

	myPostProcessor = GetOwner().AddComponent<PostProcessor>();
	myPostProcessor->Initialize();
	//myPostProcessor->AddEffect(Graphics::EffectType::Skinning);
	//to test
	//myPostProcessor->AddEffect(Graphics::EffectType::CellShader);

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
	GetModelUI();

	if (mModel == nullptr)
	{
		//if (ImGui::Button("Load Model"))
		//{
		//	modelImporterFileBrowser->Open();
		//}
		//
		//modelImporterFileBrowser->Display();
		//LoadModel();
	}
	if(mModel)
	{
		HandleSkeletonUI();
	}
}
void Vishv::Components::Model3D::GetModelUI()
{
	if (!ImGui::CollapsingHeader("Set Model"))
		return;

	auto& models = mModelService->GetModels();
	static std::string currentItem = "";
	bool isSelected = false;
	static int selectedIndex = -1;

	if (ImGui::BeginCombo("##ModelCombo", currentItem.c_str()))
	{
		for (size_t i = 0; i < models.size(); ++i)
		{
			isSelected = (currentItem == models[i].ModelName);
			if (ImGui::Selectable(models[i].ModelName, isSelected))
				currentItem = models[i].ModelName;
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
				selectedIndex = static_cast<int>(i);
			}
		}
		ImGui::EndCombo();
	}

	if (ImGui::Button("Set") && selectedIndex >= 0)
	{
		SetModel(models[selectedIndex].model);

		if (models[selectedIndex].mAnimations.animationClips.size() > 0)
		{
			if (!myAnimation)
			{
				myAnimation = GetOwner().AddComponent<Animation3D>();
				myAnimation->Initialize();
			}

			myAnimation->SetAnimations(models[selectedIndex].mAnimations);
		}
	}
}


void Vishv::Components::Model3D::HandleSkeletonUI()
{
	if (!ImGui::CollapsingHeader("Skeleton"))
		return;

	ImGui::Checkbox("Show Skeleton", &mShowSkeleton);

	if (ImGui::CollapsingHeader("Bone Colors"))
		if (ImGui::ColorEdit4("Shallow Color", &mSkelUI.shallowC.r) || ImGui::ColorEdit4("Deep Color", &mSkelUI.deepC.r))
			mSkelUI.SetBoneDebugColour();
	mSkelUI.ShowBoneHirarchy();
}

void Vishv::Components::Model3D::SimpleDraw()
{
	if (!mShowSkeleton && !myAnimation)
		return;

	for (size_t i = 0; i < mModel->skeleton.bones.size(); ++i)
	{
		Vishv::Math::Matrix4 mat = myAnimation->mBoneTransforms[i] * myTransformation->GetTransformMatrix();// mModel->mTPosToParent[i] * mModel->skeleton.bones[i].get()->offsetTransform;
	
		Vishv::Graphics::SimpleDraw::AddSphere({ mat._41, mat._42, mat._43 }, 3.0f,mModel->skeleton.bones[i]->mDebugColor, 4, 4);
		for (size_t j = 0; j < mModel->skeleton.bones[i]->children.size(); ++j)
		{
			Vishv::Math::Matrix4 matC;
			matC = myAnimation->mBoneTransforms[mModel->skeleton.bones[i]->children[j]->index] * myTransformation->GetTransformMatrix(); //mModel->mTPosToParent[mModel->skeleton.bones[i]->childIndicies[j]];
			Vishv::Graphics::SimpleDraw::AddLine(mat.GetTranslation(), matC.GetTranslation(), mModel->skeleton.bones[i]->mDebugColor);
		}
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
	mSkelUI.SetSkeleton(mModel->skeleton);
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

	mSkelUI.SetSkeleton(mModel->skeleton);
}

void Vishv::Components::Model3D::Render()
{
	if (!mModel || mShowSkeleton)
		return;

	auto em = Graphics::EffectsManager::Get();
	auto type = myPostProcessor->GetCurrentEffect();

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

#pragma region Skeleton UI Class Region

uint32_t Model3D::SkeletonUI::GetDepth()
{
	return getDepth(mSkeleton->root);
}
void Model3D::SkeletonUI::SetBoneDebugColour()
{
	setDebugColor(mSkeleton->root, 0, GetDepth());
}
void Model3D::SkeletonUI::ShowBoneHirarchy()
{
	if (!ImGui::CollapsingHeader("Skeleton Bones"))
		return;
	WriteBoneNameAndCallChildren(mSkeleton->root);
}

uint32_t Model3D::SkeletonUI::getDepth(Vishv::Graphics::Bone* bone)
{
	std::vector<int> depth;
	//call the depth function on each and compare the size
	for (size_t i = 0; i < bone->children.size(); ++i)
		depth.push_back((uint32_t)getDepth(bone->children[i]));

	int deepest = 0;
	for (size_t i = 0; i < depth.size(); ++i)
		if (depth[i] > deepest)
			deepest = depth[i];

	return deepest + 1;
}
void Model3D::SkeletonUI::setDebugColor(Vishv::Graphics::Bone* bone, uint32_t currentDepth, uint32_t totalDepth)
{
	float ratio = static_cast<float>(currentDepth) / static_cast<float>(totalDepth);
	bone->mDebugColor = Vishv::Math::Vector4::Interpolate(shallowC, deepC, ratio);

	for (size_t i = 0; i < bone->children.size(); ++i)
		setDebugColor(bone->children[i], currentDepth + 1, totalDepth);
}

void Model3D::SkeletonUI::WriteBoneNameAndCallChildren(Vishv::Graphics::Bone* bone)
{
	if (ImGui::CollapsingHeader(bone->name.c_str()))
		for (size_t i = 0; i < bone->children.size(); ++i)
			WriteBoneNameAndCallChildren(bone->children[i]);
}

#pragma endregion


