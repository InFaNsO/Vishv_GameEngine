#include "AnimationSet_Gui.h"

using namespace Vishv;
using namespace Vishv::UI;

namespace
{
	enum class KeyType
	{
		position, rotation, scale
	};

	void KeyDataPosition(Vishv::Graphics::PositionKeyframe& key)
	{
		ImGui::DragFloat3("Position ", &key.value.x, 0.1f);

	}
	void KeyDataRotation(Vishv::Graphics::RotationKeyframe& key)
	{
		Math::Vector3 rot;
		if (ImGui::DragFloat3("Rotation ", &rot.x, 0.1f))
		{
			key.value *= Math::Quaternion::RotationQuaternion(rot.x, { 1.0f,0.0f,0.0f }) * Math::Quaternion::RotationQuaternion(rot.y, { 0.0f,1.0f,0.0f }) * Math::Quaternion::RotationQuaternion(rot.z, { 0.0f,0.0f,1.0f });
			key.value.Normalize();
		}
	}
	void KeyDataScale(Vishv::Graphics::ScaleKeyframe& key)
	{
		ImGui::DragFloat3("Scale ", &key.value.x, 0.1f);
	}

	//void ShowKeyData(Vishv::Graphics::Keyframe<T>& key)
	//{
	//	if constexpr (type == KeyType::position)
	//	else if constexpr (type == KeyType::rotation)
	//	{
	//
	//	}
	//	else
	//}
}

void Vishv::UI::AnimationSetUI::BoneAnimationSeting(Vishv::Graphics::BoneAnimation * animation)
{
	ImGui::Text("Index: %i", animation->index);

	static int KeyIndexPos = -1;
	static int KeyIndexScale = -1;
	static int KeyIndexRotation = -1;

	//say key type, make a slider with key index min to max the current slider will show the key data and allow it to be edited
	if (ImGui::SliderInt("Position Keys", &KeyIndexPos, 0, animation->animation.GetPositionKeys().size()))
		KeyDataPosition(animation->animation.GetPositionKeys()[KeyIndexPos]);
	else if (ImGui::SliderInt("Rotation Keys", &KeyIndexPos, 0, animation->animation.GetRotationKeys().size()))
		KeyDataRotation(animation->animation.GetRotationKeys()[KeyIndexPos]);
	else if (ImGui::SliderInt("Scale Keys", &KeyIndexPos, 0, animation->animation.GetScaleKeys().size()))
		KeyDataScale(animation->animation.GetScaleKeys()[KeyIndexPos]);
}

void Vishv::UI::AnimationSetUI::AnimationSettings(size_t animationID)
{
	auto animation = animationSet->animationClips[animationID].get();
	//set looping
	ImGui::Text("Duration: %f", animation->duration);
	ImGui::Text("Tick//sec: %f", animation->ticksPerSecond);
	if (ImGui::Checkbox("Is Looping", &animation->isLooping))
		for (size_t i = 0; i < animation->boneAnimations.size(); ++i)
			animation->boneAnimations[i]->animation.SetLooping(animation->isLooping);

	if (ImGui::CollapsingHeader("Individual Bone Animations"))
	{
		for (size_t i = 0; i < animation->boneAnimations.size(); ++i)
			if(ImGui::CollapsingHeader(animation->boneAnimations[i]->name.c_str()))
				BoneAnimationSeting(animation->boneAnimations[i].get());
	}

}

void Vishv::UI::AnimationSetUI::DrawBlendUI()
{
	if (ImGui::CollapsingHeader("Blending"))
	{
		static int nextID = (int)next;

		ImGui::Text(ToString(current).c_str());
		if (ImGui::SliderInt("Next Animation ID", &nextID, (int)AnimationMovement::none, (int)AnimationMovement::Count) || current != next)
		{
			if(ImGui::Button("Select"))
				switchNow = true;
			next = (AnimationMovement)nextID;
		}
		ImGui::Text(ToString(next).c_str());
	}
}

AnimationMovement Vishv::UI::AnimationSetUI::GetBlendMovement(std::vector<AnimationMovement>& animations)
{
	if (!switchNow)
		return AnimationMovement::none;

	switchNow = false;
	bool found = false;
	for (size_t i = 0; i < animations.size(); ++i)
	{
		if (animations[i] == next)
		{
			found = true;
			break;
		}
	}

	if (!found)
		return AnimationMovement::none;
	current = next;
	return current;
}


std::string Vishv::UI::AnimationSetUI::ToString(AnimationMovement move)
{
	{
		switch (move)
		{
		case AnimationMovement::IdleStanding1:
			return "IdleStanding1";
			break;
		case AnimationMovement::IdleStanding2:
			return "IdleStanding2";
			break;
		case AnimationMovement::IdleCrouching1:
			return "IdleCrouching1";
			break;
		case AnimationMovement::IdleCrouching2:
			return "IdleCrouching2";
			break;
		case AnimationMovement::IdleAiming1:
			return "IdleAiming1";
			break;
		case AnimationMovement::IdleAiming2:
			return "IdleAiming2";
			break;
		case AnimationMovement::WalkForward:
			return "WalkForward";
			break;
		case AnimationMovement::WalkLeft:
			return "WalkLeft";
			break;
		case AnimationMovement::WalkRight:
			return "WalkRight";
			break;
		case AnimationMovement::WalkBackward:
			return "WalkBackward";
			break;
		case AnimationMovement::CrouchWalkingForward:
			return "CrouchWalkingForward";
			break;
		case AnimationMovement::CrouchWalkingLeft:
			return "CrouchWalkingLeft";
			break;
		case AnimationMovement::CrouchWalkingRight:
			return "CrouchWalkingRight";
			break;
		case AnimationMovement::CrouchWalkingBackward:
			return "CrouchWalkingBackward";
			break;
		case AnimationMovement::AimWalkingForward:
			return "AimWalkingForward";
			break;
		case AnimationMovement::AimWalkingLeft:
			return "AimWalkingLeft";
			break;
		case AnimationMovement::AimWalkingRight:
			return "AimWalkingRight";
			break;
		case AnimationMovement::AimWalkingBackward:
			return "AimWalkingBackward";
			break;
		default:
			return "empty";
			break;
		}
	}
}

void Vishv::UI::AnimationSetUI::DrawUI()
{
	ImGui::Begin("Aniamtion Set");

	ImGui::Text("Number of animations: %i", animationSet->animationClips.size());
	ImGui::DragFloat("Animation Blend Time", &animationSet->blendTimer, 0.1f, 1.0f, 3.0f);

	DrawBlendUI();

	for (size_t i = 0; i < animationSet->animationClips.size(); ++i)
	{
		if (animationSet->animationClips[i] == nullptr)
			continue;
		if (ImGui::CollapsingHeader(animationSet->animationClips[i]->name.c_str()))
		{
			AnimationSettings(i);
		}
	}

	ImGui::End();
}



