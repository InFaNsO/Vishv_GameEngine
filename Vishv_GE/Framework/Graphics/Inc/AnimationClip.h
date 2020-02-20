#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATION_CLIP_H
#define INCLUDED_VISHV_GRAPHICS_ANIMATION_CLIP_H

#include "Animation.h"

namespace Vishv::Graphics
{
	struct AnimationClip
	{
		bool GetTransform(float time, size_t boneIndex, Math::Matrix4& transform);
		bool GetTransform(float time, size_t boneIndex, Math::Vector3& position, Math::Quaternion& rotation);

		bool isLooping = false;
		std::string name;
		float duration = 0.0f;
		float ticksPerSecond = 0.0f;
		BoneAnimations boneAnimations;
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_ANIMATION_CLIP


