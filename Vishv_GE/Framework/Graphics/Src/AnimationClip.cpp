#include "Precompiled.h"
#include "AnimationClip.h"

bool Vishv::Graphics::AnimationClip::GetTransform(float time, size_t boneIndex, Math::Matrix4 & transform)
{
	auto& boneAnim = boneAnimations[boneIndex];
	if (boneAnim)
	{
		transform = boneAnim->animation.GetTransformation(time);
		return true;
	}

	return false;
}

bool Vishv::Graphics::AnimationClip::GetTransform(float time, size_t boneIndex, Math::Vector3 & position, Math::Quaternion & rotation)
{
	auto& boneAnim = boneAnimations[boneIndex];
	if (boneAnim)
	{
		boneAnim->animation.GetTransformation(time, position, rotation);
		return true;
	}
	return false;
}

