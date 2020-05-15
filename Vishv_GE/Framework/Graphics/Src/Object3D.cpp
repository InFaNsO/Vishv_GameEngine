#include "Precompiled.h"
#include "Object3D.h"
#include "MeshBuilder.h"
#include "MeshIO.h"
#include "Camera.h"
#include "EffectsManager.h"
#include "TextureManager.h"
#include "SamplerManager.h"

using namespace Vishv::Graphics;

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

void Vishv::Graphics::Object3D::Set(MeshShape shape)
{
	Model::MeshData<BoneMesh> md;
	switch (shape)
	{
	case Vishv::Graphics::MeshShape::Cylinder:
		md.mMesh = Vishv::Graphics::Meshbuilder::CreateBoneCylinder(12, 12, 1.0f, 1, 12);
		md.mBuffer.Initialize(md.mMesh);
		mModel.model.mMeshes.emplace_back(std::move(md));
		break;
	case Vishv::Graphics::MeshShape::Sphere:
		break;
	case Vishv::Graphics::MeshShape::Cube:
		md.mMesh = Vishv::Graphics::Meshbuilder::CreateBoneCube(1.0f, 1.0f, 1.0f, 1);
		md.mBuffer.Initialize(md.mMesh);
		mModel.model.mMeshes.emplace_back(std::move(md));
		break;
	default:
		break;
	}
}

void Vishv::Graphics::Object3D::Set(std::filesystem::path modelPath)
{
	MeshIO mio;
	mio.LoadMeshGeneral(modelPath);
	mio.GetModel(mModel.model);

	auto textureManager = Vishv::Graphics::TextureManager::Get();
	for (uint32_t i = 0; i < mModel.model.mMaterials.size(); ++i)
	{
		auto& material = mModel.model.mMaterials[i];
		if (material.diffuseName != "empty")
			material.diffuseID = textureManager->LoadTexture(material.diffuseName, false);
		else
			material.diffuseID = textureManager->LoadTexture("black.jpg");
		if (material.bumpName != "empty")
			material.bumpID = textureManager->LoadTexture(material.bumpName, false);
		else
			material.bumpID= textureManager->LoadTexture("black.jpg"); 
		if (material.normalName != "empty")
			material.normalID = textureManager->LoadTexture(material.normalName, false);
		else
			material.normalID = textureManager->LoadTexture("black.jpg"); 
		if (material.specularName != "empty")
			material.specularID = textureManager->LoadTexture(material.specularName, false);
		else
			material.specularID = textureManager->LoadTexture("black.jpg");
	}
	for (uint32_t i = 0; i < mModel.model.mMeshes.size(); ++i)
	{
		mModel.model.mMeshes[i].mBuffer.Initialize(mModel.model.mMeshes[i].mMesh);
	}
}

void Vishv::Graphics::Object3D::UpdateBlend(size_t currentAnimationID, size_t finalAnimationID, float ratio)
{
	/*VISHVASSERT(currentAnimationID < mModel.animations->animationClips.size(), "[Object 3D] animation Index out of range");
	VISHVASSERT(finalAnimationID < mModel.animations->animationClips.size(), "[Object 3D] animation Index out of range");

	Vishv::Math::Vector3 posAnim1, posAnim2;
	Vishv::Math::Quaternion rotAnim1, rotAnim2;

	for (size_t i = 0; i < mModel.skeleton.GetBoneArray().size(); ++i)
	{
		auto& bone = mModel.skeleton.GetBoneArray()[i];
		auto& currentAnimation = mModel.animations->animationClips[mModel.playAnimations[currentAnimationID].animationIndex];
		auto& finalAnimation = mModel.animations->animationClips[mModel.playAnimations[finalAnimationID].animationIndex];

		bool isFirst = currentAnimation->GetTransform(mModel.playAnimations[currentAnimationID].time, i, posAnim1, rotAnim1);
		bool isSecond = finalAnimation->GetTransform(mModel.playAnimations[finalAnimationID].time, i, posAnim2, rotAnim2);

		float r1 = EaseCalculation::GetTime(ratio, mModel.playAnimations[currentAnimationID].mEasingType, false);
		float r2 = EaseCalculation::GetTime(ratio, mModel.playAnimations[finalAnimationID].mEasingType, false);

		if (!isFirst && !isSecond)
			tPoseToParents[i] = bone->toParentTransform;
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

			tPoseToParents[i] = Vishv::Math::Matrix4::TranslationMatrix(Vishv::Math::Quaternion::Slerp(rotAnim1, rotAnim2, r1), Vishv::Math::Vector3::Lerp(posAnim1, posAnim2, r2));
		}
	}

	UpdateTransform<true>(mModel.skeleton.root, boneTransforms, tPoseToParents);
}

void Vishv::Graphics::Object3D::Update(size_t animationIndex, bool isPlaying, bool pause)
{
	VISHVASSERT(animationIndex < mModel.animations->animationClips.size(), "[Object 3D] animation Index out of range");

	static bool doIt = true;

	if (isPlaying && !pause)
	{
		for (size_t i = 0; i < mModel.skeleton.GetBoneArray().size(); ++i)
		{
			auto& bone = mModel.skeleton.GetBoneArray()[i];
			auto& currentAnimation = mModel.animations->animationClips[mModel.playAnimations[animationIndex].animationIndex];

			if (!currentAnimation->GetTransform(mModel.playAnimations[animationIndex].time, i, tPoseToParents[i]))
			{
				tPoseToParents[i] = bone->toParentTransform;
			}
		}
		doIt = false;
	}
	if (isPlaying)
		UpdateTransform<true>(mModel.skeleton.root, boneTransforms, tPoseToParents);
	else
		UpdateTransform<false>(mModel.skeleton.root, boneTransforms, tPoseToParents);*/
}

void Vishv::Graphics::Object3D::Render(const Vishv::Graphics::Camera& camera, Vishv::Graphics::EffectType type, bool SceneRender)
{
	Render(camera, transform, type, SceneRender);
}


void Vishv::Graphics::Object3D::Render(const Camera & camera, Math::Transform & otherTransform, EffectType type, bool SceneRender)
{
	auto em = Graphics::EffectsManager::Get();

	auto v = camera.GetViewMatrix();
	auto p = camera.GetPerspectiveMatrix();
	auto w = Vishv::Math::Matrix4::RotateMatrix(otherTransform.Rotation()) * Vishv::Math::Matrix4::TranslateMatrix(otherTransform.mPosition);

	if (true)
	{
		em->BindEffect(type);
		em->GetBufferData(type)->GetTransform()->viewPosition = camera.GetPosition();
		em->GetBufferData(type)->GetTransform()->world = w.Transpose();
		em->GetBufferData(type)->GetTransform()->wvp = (w * v *p).Transpose();

		for (size_t i = 0; i < mModel.skeleton.GetBoneArray().size() && i < (size_t)mModel.skeleton.MaxBoneCount(); ++i)
		{
			if (SceneRender)
				em->GetBufferData(type)->GetBonetransformData()->boneTransforms[i] = (mModel.skeleton.bones[i]->offsetTransform * boneTransforms[i]/* * tPoseToParents[i]*/).Transpose();	//multipy bone transformation aswell

		}

		em->Set(type);
		em->BindBuffer(type);
	}
	//else
	//{
	//	em->BindEffect(type);
	//	em->GetBufferData(type)->GetTextureing()->wvp = (w * v *p).Transpose();
	//	em->Set(type);
	//	em->BindBuffer(type);
	//}
	mModel.model.Render();
}

