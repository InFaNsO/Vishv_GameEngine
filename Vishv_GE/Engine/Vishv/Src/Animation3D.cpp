#include "Precompiled.h"
#include "Animation3D.h"

#include "Model3D.h"
#include "TransformComponent.h"

using namespace Vishv;
using namespace Components;

META_DERIVED_BEGIN(Animation3D, Component)
	META_FIELD_BEGIN
	META_FIELD_END
META_CLASS_END

namespace
{
	using namespace Graphics;

	template <bool UseAnimation>
	void UpdateTransform(const Bone* bone, std::vector<Vishv::Math::Matrix4>& boneMatrix, const std::vector<Vishv::Math::Matrix4>& animate)
	{
		if (bone->parent)
		{
			if constexpr (UseAnimation)
				boneMatrix[bone->index] = ((animate[bone->index])) * boneMatrix[bone->parentId];
			else
				boneMatrix[bone->index] = (bone->toParentTransform) * boneMatrix[bone->parentId];
		}
		else
		{
			if constexpr (UseAnimation)
				boneMatrix[bone->index] = (animate[bone->index]);// *bone->toParentTransform;
			else
				boneMatrix[bone->index] = (bone->toParentTransform);
		}

		for (auto child : bone->children)
		{
			UpdateTransform<UseAnimation>(child, boneMatrix, animate);
		}
	}
}


void Vishv::Components::Animation3D::Initialize()
{
	myTransform = GetOwner().GetComponent<TransformComponent>();
	myModel = GetOwner().GetComponent<Model3D>();
	VISHVASSERT(!myModel, "[Aniamtion3D] The objects needs a Model 3D component to apply animation first");

	myModel->myAnimation = this;
	mBoneTransforms.resize(myModel->mModel->mTPosToParent.size());
}

void Vishv::Components::Animation3D::Update()
{
	if (!mAniamtionStateMachine)
		return;

	mAniamtionStateMachine->GetBoneTransforms(mBoneTransforms);
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



