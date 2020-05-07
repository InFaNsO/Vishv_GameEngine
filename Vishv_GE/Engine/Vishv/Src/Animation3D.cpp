#include "Precompiled.h"
#include "Animation3D.h"

#include "Model3D.h"
#include "TransformComponent.h"

#include "imfilebrowser.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(Animation3D, Component)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END

namespace
{
	std::unique_ptr<ImGui::FileBrowser> animImporterFileBrowser = nullptr;
}


void Vishv::Components::Animation3D::Initialize()
{
	myTransform = GetOwner().GetComponent<TransformComponent>();
	myModel = GetOwner().GetComponent<Model3D>();
	VISHVASSERT(myModel, "[Aniamtion3D] The objects needs a Model 3D component to apply animation first");

	myModel->myAnimation = this;
	mBoneTransforms.resize(myModel->mModel->mTPosToParent.size());

	//temp
	mAnimations = new Graphics::AnimationSet();

	//setup file browser
	animImporterFileBrowser = std::make_unique<ImGui::FileBrowser>(ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_EnterNewFilename);
	animImporterFileBrowser->SetTitle("Model & Import");
	animImporterFileBrowser->SetPwd(Graphics::TextureManager::Get()->GetRootPath());
	animImporterFileBrowser->SetTypeFilters({ ".vanim"});


}

void Vishv::Components::Animation3D::Update()
{
	if (!mAniamtionStateMachine)
		return;

	mAniamtionStateMachine->GetBoneTransforms(mBoneTransforms);
}

void Vishv::Components::Animation3D::DebugUI()
{
	if (ImGui::SliderInt("Index", &currentAnim, 0, static_cast<int>(mAnimations->animationClips.size())))
	{
		mAniamtionStateMachine->SetIndex(currentAnim);
	}
	ImGui::Text(mAnimations->animationClips[currentAnim]->name.c_str());
}

void Vishv::Components::Animation3D::SetAnimations(Graphics::AnimationSet& animationSet)
{
	mAnimations = &animationSet;
		mAniamtionStateMachine = std::make_unique<Graphics::AnimationStateMachine>(*mAnimations, *myModel->mModel);
}

bool Vishv::Components::Animation3D::SetAnimationIndex(int index)
{
	return mAniamtionStateMachine->SetIndex(index);
}


void Vishv::Components::Animation3D::BindBonesToBuffer()
{
	auto em = Graphics::EffectsManager::Get();
	auto type = Graphics::EffectType::Skinning;

	auto model = myModel->mModel;

	for (size_t i = 0; i < model->skeleton.GetBoneArray().size() && i < (size_t)model->skeleton.MaxBoneCount(); ++i)
		em->GetBufferData(type)->GetBonetransformData()->boneTransforms[i] = (model->skeleton.bones[i]->offsetTransform * mBoneTransforms[i]).Transpose();	//multipy bone transformation aswell

}



