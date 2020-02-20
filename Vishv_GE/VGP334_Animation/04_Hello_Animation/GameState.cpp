#include "GameState.h"

void GameState::Initialize()
{
	Vishv::Graphics::AnimationIO aio;

	object.mModel.animations = &animations;
	animations.animationClips.push_back(std::make_unique<Vishv::Graphics::AnimationClip>());

	object.mModel.playAnimations.push_back({ 0,0.0f });
	
	std::filesystem::path path = "..\\..\\Assets\\3D_Models\\VishMesh\\Swat";
	aio.LoadAnimation(path / "IdleStanding1.vanim", *animations.animationClips.back().get());

	object.Set(path / "Swat.vmesh");
	Vishv::Graphics::SkeletonIO sio;
	sio.LoadSkeleton(path / "Swat.vskel", object.mModel.skeleton);

	object.tPoseToParents.reserve(object.mModel.skeleton.bones.size());
	for (auto& bone : object.mModel.skeleton.bones)
	{
		object.tPoseToParents.emplace_back(bone->toParentTransform);
	}

	object.boneTransforms.resize(object.mModel.skeleton.bones.size());

	depth = GetDepth(object.mModel.skeleton.root);

	SetColorBasedOnDepth(object.mModel.skeleton.root, 0, depth);

}

void GameState::SetColorBasedOnDepth(Vishv::Graphics::Bone * bone, int currentDepth, int totalDepth)
{
	float ratio = static_cast<float>(currentDepth) / static_cast<float>(totalDepth);
	bone->mDebugColor = Vishv::Math::Vector4::Interpolate(shallowC, deepC, ratio);

	for (size_t i = 0; i < bone->children.size(); ++i)
	{
		SetColorBasedOnDepth(bone->children[i], currentDepth + 1, totalDepth);
	}
}

int GameState::GetDepth(Vishv::Graphics::Bone* bone)
{
	std::vector<int> depth;

	for (size_t i = 0; i < bone->children.size(); ++i)
	{
		//call the depth function on each and compare the size
		depth.push_back(GetDepth(bone->children[i]));
	}

	int deepest = 0;
	for(size_t i = 0; i < depth.size(); ++i)
	{
		if (depth[i] > deepest)
			deepest = depth[i];
	}

	return deepest + 1;
}

void GameState::Update(float deltaTime)
{
	if (isPLaying)
	{
		object.mModel.playAnimations[0].time += deltaTime * animations.animationClips[0]->ticksPerSecond;
		if (object.mModel.playAnimations[0].time > animations.animationClips[0]->duration)
		{
			object.mModel.playAnimations[0].time = 0.0f;
		}
	}
	object.Update(0,isPLaying, isPause);
}

void GameState::RenderDebugUI()
{
	ImGui::Begin("Animation Controller");

	if (ImGui::CollapsingHeader("Controlls"))
	{
		if(ImGui::Button("Play"))
		{
			if (isPLaying)
			{
				isPLaying = false;
			}
			else
			{
				isPLaying = true;
			}
		}
		if (ImGui::Button("Pause"))
		{
			if (isPause)
			{
				isPause = false;
			}
			else
			{
				isPause = true;
			}
		}
		if (ImGui::Button("Reset"))
		{
			object.mModel.playAnimations[0].time = 0.0f;
		}

		if (ImGui::ColorEdit4("Shallow Bone Color", &shallowC.x))
		{
			SetColorBasedOnDepth(object.mModel.skeleton.root, 0, depth);
		}
		if (ImGui::ColorEdit4("Deep Bone Color", &deepC.x))
		{
			SetColorBasedOnDepth(object.mModel.skeleton.root, 0, depth);
		}
	}

	ImGui::End();
}

void GameState::RenderSimpleDraw()
{
	for (size_t i = 0; i < object.mModel.skeleton.bones.size(); ++i)
	{
		Vishv::Math::Matrix4 mat = object.boneTransforms[i];

		Vishv::Graphics::SimpleDraw::AddSphere({ mat._41, mat._42, mat._43 }, 3.0f, object.mModel.skeleton.bones[i]->mDebugColor, 4, 4);
		for (size_t j = 0; j < object.mModel.skeleton.bones[i]->children.size(); ++j)
		{
			Vishv::Math::Matrix4 matC;
				matC = object.boneTransforms[object.mModel.skeleton.bones[i]->childIndicies[j]];
			
			Vishv::Graphics::SimpleDraw::AddLine({ mat._41, mat._42, mat._43 }, { matC._41, matC._42, matC._43 }, object.mModel.skeleton.bones[i]->mDebugColor);
		}
	}
}

void GameState::Render()
{
	scene.currentEffect = Vishv::Graphics::EffectType::Mixamo;

	object.Render(*scene.sceneCamera, scene.currentEffect);
}

void GameState::Terminate()
{

}
