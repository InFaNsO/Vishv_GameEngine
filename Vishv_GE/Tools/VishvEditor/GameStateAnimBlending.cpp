#include "GameStateAnimBlending.h"

#include "AnimationSet_Gui.h"
#include "Skeleton_Gui.h"

namespace
{
	Vishv::UI::SkeletonUI skelUI;
	Vishv::UI::AnimationSetUI animUI;


}

void GameStateAnimBlending::SetAnimations(std::filesystem::path& path)
{
	//total 8 animations
	Vishv::Graphics::AnimationIO aio;

	object.mModel.animations = &animations;
	
	mMovements.reserve(8);

	animations.animationClips.resize((size_t)AnimationMovement::Count);
	object.mModel.playAnimations.resize((size_t)AnimationMovement::Count);

	for (int i = 0; i < (int)AnimationMovement::Count; ++i)
	{
		animations.animationClips[i] = nullptr;
	}

	animations.animationClips[(size_t)AnimationMovement::IdleStanding1] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::IdleStanding1) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::IdleStanding1].get());
	mMovements.emplace_back(AnimationMovement::IdleStanding1);
	object.mModel.playAnimations[(size_t)AnimationMovement::IdleStanding1] = { (int)AnimationMovement::IdleStanding1, 0.0f, animations.animationClips[(int)AnimationMovement::IdleStanding1]->duration, Vishv::Graphics::EasingHead::Sine };

	animations.animationClips[(size_t)AnimationMovement::WalkForward] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::WalkForward) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::WalkForward].get());
	mMovements.emplace_back(AnimationMovement::WalkForward);
	object.mModel.playAnimations[(size_t)AnimationMovement::WalkForward] = { (int)AnimationMovement::WalkForward, 0.0f, animations.animationClips[(int)AnimationMovement::WalkForward]->duration, Vishv::Graphics::EasingHead::Sine };

	animations.animationClips[(size_t)AnimationMovement::WalkBackward] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::WalkBackward) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::WalkBackward].get());
	mMovements.emplace_back(AnimationMovement::WalkBackward);
	object.mModel.playAnimations[(size_t)AnimationMovement::WalkBackward] = { (int)AnimationMovement::WalkBackward, 0.0f, animations.animationClips[(int)AnimationMovement::WalkBackward]->duration, Vishv::Graphics::EasingHead::Sine };

	animations.animationClips[(size_t)AnimationMovement::WalkLeft] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::WalkLeft) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::WalkLeft].get());
	mMovements.emplace_back(AnimationMovement::WalkLeft);
	object.mModel.playAnimations[(size_t)AnimationMovement::WalkLeft] = { (int)AnimationMovement::WalkLeft, 0.0f, animations.animationClips[(int)AnimationMovement::WalkLeft]->duration, Vishv::Graphics::EasingHead::Sine };

	animations.animationClips[(size_t)AnimationMovement::WalkRight] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::WalkRight) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::WalkRight].get());
	mMovements.emplace_back(AnimationMovement::WalkRight);
	object.mModel.playAnimations[(size_t)AnimationMovement::WalkRight] = { (int)AnimationMovement::WalkRight, 0.0f, animations.animationClips[(int)AnimationMovement::WalkRight]->duration, Vishv::Graphics::EasingHead::Sine };

	animations.animationClips[(size_t)AnimationMovement::IdleCrouching1] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::IdleCrouching1) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::IdleCrouching1].get());
	mMovements.emplace_back(AnimationMovement::IdleCrouching1);
	object.mModel.playAnimations[(size_t)AnimationMovement::IdleCrouching1] = { (int)AnimationMovement::IdleCrouching1, 0.0f, animations.animationClips[(int)AnimationMovement::IdleCrouching1]->duration, Vishv::Graphics::EasingHead::Sine };

	animations.animationClips[(size_t)AnimationMovement::CrouchWalkingForward] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::CrouchWalkingForward) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::CrouchWalkingForward].get());
	mMovements.emplace_back(AnimationMovement::CrouchWalkingForward);
	object.mModel.playAnimations[(size_t)AnimationMovement::CrouchWalkingForward] = { (int)AnimationMovement::CrouchWalkingForward, 0.0f, animations.animationClips[(int)AnimationMovement::CrouchWalkingForward]->duration, Vishv::Graphics::EasingHead::Sine };

	animations.animationClips[(size_t)AnimationMovement::CrouchWalkingBackward] = std::make_unique<Vishv::Graphics::AnimationClip>();
	aio.LoadAnimation(path / (animUI.ToString(AnimationMovement::CrouchWalkingBackward) + ".vanim"), *animations.animationClips[(size_t)AnimationMovement::CrouchWalkingBackward].get());
	mMovements.emplace_back(AnimationMovement::CrouchWalkingBackward);
	object.mModel.playAnimations[(size_t)AnimationMovement::CrouchWalkingBackward] = { (int)AnimationMovement::CrouchWalkingBackward, 0.0f, animations.animationClips[(int)AnimationMovement::CrouchWalkingBackward]->duration, Vishv::Graphics::EasingHead::Sine };

	for (size_t i = 0; i < animations.animationClips.size(); ++i)
	{
		if (animations.animationClips[i] == nullptr)
			continue;
		animations.animationClips[i]->isLooping = true;
	}
}


void GameStateAnimBlending::Initialize()
{
	std::filesystem::path path = "..\\..\\Assets\\3D_Models\\VishMesh\\Swat";

	SetAnimations(path);

	object.Set(path / "Swat.vmesh");
	Vishv::Graphics::SkeletonIO sio;
	sio.LoadSkeleton(path / "Swat.vskel", object.mModel.skeleton);

	object.tPoseToParents.reserve(object.mModel.skeleton.bones.size());
	for (auto& bone : object.mModel.skeleton.bones)
	{
		object.tPoseToParents.emplace_back(bone->toParentTransform);
	}

	object.boneTransforms.resize(object.mModel.skeleton.bones.size());

	skelUI.SetSkeleton(object.mModel.skeleton);
	skelUI.SetBoneDebugColour(shallowC, deepC);
	animUI.SetAnimationSet(object.mModel.animations);
	animUI.SetCurrrentAnimation(AnimationMovement::IdleStanding1);
}

void GameStateAnimBlending::UpdateAnimationPlay(Vishv::Graphics::AnimationPlayInformation & play, float deltaTime)
{
	play.time += deltaTime * animations.animationClips[play.animationIndex]->ticksPerSecond;
	if (play.time > play.maxTime && animations.animationClips[play.animationIndex]->isLooping)
		play.time = 0.0f;
	else if (play.time > play.maxTime && !animations.animationClips[play.animationIndex]->isLooping)
		shouldPlay = false;
}

void GameStateAnimBlending::Update(float deltaTime)
{
	if (!shouldBlend)
	{
		nextAnimation = animUI.GetBlendMovement(mMovements);
		if (nextAnimation != AnimationMovement::none)
		{
			shouldPlay = true;
			shouldBlend = true;
			object.mModel.playAnimations[(size_t)nextAnimation].time = 0.0f;
		}
	}
	if (blendTimer >= blendTimeTotal && shouldBlend)
	{
		blendTimer = 0.0f;
		shouldBlend = false;
		currentAnimation = nextAnimation;
		nextAnimation = AnimationMovement::none;
	}

	if (shouldBlend)
	{
		blendTimer += deltaTime;
		
		blendTimer = blendTimer > blendTimeTotal ? blendTimeTotal : blendTimer;

		UpdateAnimationPlay(object.mModel.playAnimations[(size_t)currentAnimation], deltaTime);
		UpdateAnimationPlay(object.mModel.playAnimations[(size_t)nextAnimation], deltaTime);

		object.UpdateBlend(object.mModel.playAnimations[(size_t)currentAnimation].animationIndex, (size_t)nextAnimation, blendTimer / blendTimeTotal);
	}
	else
	{
		auto& play = object.mModel.playAnimations[(size_t)currentAnimation];
		UpdateAnimationPlay(play, deltaTime);

		object.Update((size_t)currentAnimation, shouldPlay);
	}

}

void GameStateAnimBlending::Render()
{
	scene.currentEffect = Vishv::Graphics::EffectType::Mixamo;

	object.Render(*scene.sceneCamera, scene.currentEffect);
}

void GameStateAnimBlending::RenderDebugUI()
{
	//ImGui::Begin("App UI");
	//
	//ImGui::DragFloat("BlendDuration", &blendTimeTotal, 0.1f, 0.1f);
	//if (ImGui::CollapsingHeader("Bone Color"))
	//{
	//	if (ImGui::ColorEdit4("Shallow Color", &shallowC.r) || ImGui::ColorEdit4("Deep Color", &deepC.r))
	//		skelUI.SetBoneDebugColour(shallowC, deepC);
	//}
	//
	//animUI.DrawUI();
	//skelUI.ShowBoneHirarchy();
	//
	//ImGui::End();
}

void GameStateAnimBlending::Terminate()
{
}

void GameStateAnimBlending::RenderSimpleDraw()
{
	for (size_t i = 0; i < object.mModel.skeleton.bones.size(); ++i)
	{
		Vishv::Math::Matrix4 mat = object.boneTransforms[i];

		Vishv::Graphics::SimpleDraw::AddSphere({ mat._41, mat._42, mat._43 }, 3.0f, object.mModel.skeleton.bones[i]->mDebugColor, 4, 4);
		for (size_t j = 0; j < object.mModel.skeleton.bones[i]->children.size(); ++j)
		{
			Vishv::Math::Matrix4 matC;
			matC = object.boneTransforms[object.mModel.skeleton.bones[i]->childIndicies[j]];

			Vishv::Graphics::SimpleDraw::AddLine(mat.GetTranslation(),  matC.GetTranslation(), object.mModel.skeleton.bones[i]->mDebugColor);
		}
	}
}



