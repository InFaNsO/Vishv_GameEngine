#include "Precompiled.h"
#include "ModelAnimation.h"
#include "TransformComponent.h"
#include "GameWorld.h"


size_t invalidIndexAinm = (size_t)UINT64_MAX;

META_DERIVED_BEGIN(Vishv::Components::ModelAnimation, Vishv::Components::Component)
META_FIELD_BEGIN
META_FIELD(mBoneTransforms, "BoneTransforms")
META_FIELD(mTPosToParents, "ToParent")
META_FIELD(mBlendTimeTotal , "BlendTimer")
		//META_FIELD(mModel, "RiggedModel")
	META_FIELD_END
META_CLASS_END

using namespace Vishv::Components;


void Vishv::Components::ModelAnimation::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mNextAnimationIndex = invalidIndexAinm;
}

void Vishv::Components::ModelAnimation::UpdateAnimationPlayInformation(Graphics::AnimationPlayInformation & play, float deltaTime)
{
	play.time += deltaTime * mModel->animations->animationClips[play.animationIndex]->ticksPerSecond;
	if (play.time > play.maxTime && mModel->animations->animationClips[play.animationIndex]->isLooping)
		play.time = deltaTime;
	else if (play.time > play.maxTime && !mModel->animations->animationClips[play.animationIndex]->isLooping)
		mNextAnimationIndex = 0;
}

void Vishv::Components::ModelAnimation::Update(float deltaTime)
{
	//take input and then select which update to call
	//graphic obj update
	if (!mShouldBlend && mNextAnimationIndex != invalidIndexAinm)
	{
		mShouldPlay = true;
		mShouldBlend = true;
		mModel->playAnimations[mNextAnimationIndex].time = 0.0f;
	}
	if (mBlendTimer >= mBlendTimeTotal && mShouldBlend)
	{
		mBlendTimer = 0.0f;
		mShouldBlend = false;
		mCurrentAnimationIndex = mNextAnimationIndex;
		mNextAnimationIndex = invalidIndexAinm;
	}

	if (mShouldBlend)
	{
		mBlendTimer += deltaTime;
		mBlendTimer = mBlendTimer > mBlendTimeTotal ? mBlendTimeTotal : mBlendTimer;

		UpdateAnimationPlayInformation(mModel->playAnimations[mCurrentAnimationIndex], deltaTime);
		UpdateAnimationPlayInformation(mModel->playAnimations[mNextAnimationIndex], deltaTime);

		UpdateBlend(mModel->playAnimations[mCurrentAnimationIndex].animationIndex, mNextAnimationIndex, mBlendTimer / mBlendTimeTotal);
	}
	else
	{
		auto& play = mModel->playAnimations[mCurrentAnimationIndex];
		UpdateAnimationPlayInformation(play, deltaTime);

		Update(mCurrentAnimationIndex, mShouldPlay);
	}
}

void Vishv::Components::ModelAnimation::SimpleDraw()
{
	//draw the skeleton
}

void Vishv::Components::ModelAnimation::DebugUI()
{
	if (!ImGui::CollapsingHeader(StaticGetMetaClass()->GetName()))
		return;

}

void Vishv::Components::ModelAnimation::Render()
{
	//call the other render
	//make a world class // change scene into world
	Render(*GetOwner().GetWorld().GetMainCamera(), Graphics::EffectType::Skinning);
}

void Vishv::Components::ModelAnimation::Terminate()
{
	//remove things needed
	if (mModel != nullptr)
	{
		delete mModel;
		mModel = nullptr;
	}
}

bool Vishv::Components::ModelAnimation::IsNextAnim()
{
	if (mNextAnimationIndex == invalidIndexAinm)
		return false;
	return true;
}

using namespace Vishv::Graphics;

void Vishv::Components::ModelAnimation::Set(std::filesystem::path modelPath, std::string modelName, Vishv::Graphics::AnimationSet& animation)
{
	if (mModel == nullptr)
		mModel = new Graphics::RiggedModel;


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

	mModel->animations = &animation;

	SetUp();

}

void Vishv::Components::ModelAnimation::Set(Graphics::RiggedModel & model)
{
	mModel = &model;
	SetUp();
}





namespace
{
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

void Vishv::Components::ModelAnimation::SetUp()
{
	mTPosToParents.reserve(mModel->skeleton.bones.size());
	for (auto& bone : mModel->skeleton.bones)
		mTPosToParents.emplace_back(bone->toParentTransform);

	mBoneTransforms.resize(mTPosToParents.size());

	mModel->playAnimations.resize(mModel->animations->animationClips.size());

	for(size_t i = 0; i < mModel->playAnimations.size(); ++i)
	{
		mModel->playAnimations[i].animationIndex = (int)i;
		if(mModel->animations->animationClips[i] != nullptr)
			mModel->playAnimations[i].maxTime = mModel->animations->animationClips[i].get()->duration;
	}
}

void Vishv::Components::ModelAnimation::Update(size_t animationIndex, bool isPlaying, bool pause)
{
	VISHVASSERT(animationIndex < mModel->animations->animationClips.size(), "[Object 3D] animation Index out of range");

	static bool doIt = true;

	if (isPlaying && !pause)
	{
		for (size_t i = 0; i < mModel->skeleton.GetBoneArray().size(); ++i)
		{
			auto& bone = mModel->skeleton.GetBoneArray()[i];
			auto& currentAnimation = mModel->animations->animationClips[mModel->playAnimations[animationIndex].animationIndex];

			if (!currentAnimation->GetTransform(mModel->playAnimations[animationIndex].time, i, mTPosToParents[i]))
			{
				mTPosToParents[i] = bone->toParentTransform;
			}
		}
		doIt = false;
	}
	if (isPlaying)
		UpdateTransform<true>(mModel->skeleton.root, mBoneTransforms, mTPosToParents);
	else
		UpdateTransform<false>(mModel->skeleton.root, mBoneTransforms, mTPosToParents);
}

void Vishv::Components::ModelAnimation::Render(const Graphics::Camera & camera, Graphics::EffectType type)
{
	auto em = Graphics::EffectsManager::Get();

	auto v = camera.GetViewMatrix();
	auto p = camera.GetPerspectiveMatrix();
	auto w = Vishv::Math::Matrix4::RotateMatrix(mTransformComponent->Rotation().GetConjugate()) * Vishv::Math::Matrix4::TranslateMatrix(mTransformComponent->Position());
	em->BindEffect(type);
	em->GetBufferData(type)->GetTransform()->viewPosition = camera.GetPosition();
	em->GetBufferData(type)->GetTransform()->world = w.Transpose();
	em->GetBufferData(type)->GetTransform()->wvp = (w * v *p).Transpose();

	for (size_t i = 0; i < mModel->skeleton.GetBoneArray().size() && i < (size_t)mModel->skeleton.MaxBoneCount(); ++i)
		em->GetBufferData(type)->GetBonetransformData()->boneTransforms[i] = (mModel->skeleton.bones[i]->offsetTransform * mBoneTransforms[i]/* * tPoseToParents[i]*/).Transpose();	//multipy bone transformation aswell

	em->Set(type);
	em->BindBuffer(type);
	
	mModel->model.Render();
}

void Vishv::Components::ModelAnimation::UpdateBlend(size_t currentAnimationID, size_t finalAnimationID, float ratio)
{
	VISHVASSERT(currentAnimationID < mModel->animations->animationClips.size(), "[Object 3D] animation Index out of range");
	VISHVASSERT(finalAnimationID < mModel->animations->animationClips.size(), "[Object 3D] animation Index out of range");

	Vishv::Math::Vector3 posAnim1, posAnim2;
	Vishv::Math::Quaternion rotAnim1, rotAnim2;

	for (size_t i = 0; i < mModel->skeleton.GetBoneArray().size(); ++i)
	{
		auto& bone = mModel->skeleton.GetBoneArray()[i];
		auto& currentAnimation = mModel->animations->animationClips[mModel->playAnimations[currentAnimationID].animationIndex];
		auto& finalAnimation = mModel->animations->animationClips[mModel->playAnimations[finalAnimationID].animationIndex];

		bool isFirst = currentAnimation->GetTransform(mModel->playAnimations[currentAnimationID].time, i, posAnim1, rotAnim1);
		bool isSecond = finalAnimation->GetTransform(mModel->playAnimations[finalAnimationID].time, i, posAnim2, rotAnim2);

		float r1 = EaseCalculation::GetTime(ratio, mModel->playAnimations[currentAnimationID].mEasingType, false);
		float r2 = EaseCalculation::GetTime(ratio, mModel->playAnimations[finalAnimationID].mEasingType, false);

		if (!isFirst && !isSecond)
			mTPosToParents[i] = bone->toParentTransform;
		else
		{
			if (!isFirst)
			{
				posAnim1 = bone->toParentTransform.GetTranslation();
				rotAnim1 = Math::Quaternion::MatrixToQuaternion(bone->toParentTransform);
			}
			else if (!isSecond)
			{
				posAnim2 = bone->toParentTransform.GetTranslation();
				rotAnim2 = Math::Quaternion::MatrixToQuaternion(bone->toParentTransform);
			}

			mTPosToParents[i] = Vishv::Math::Matrix4::TranslationMatrix(Vishv::Math::Quaternion::Slerp(rotAnim1, rotAnim2, r1), Vishv::Math::Vector3::Lerp(posAnim1, posAnim2, r2));
		}
	}

	UpdateTransform<true>(mModel->skeleton.root, mBoneTransforms, mTPosToParents);
}

