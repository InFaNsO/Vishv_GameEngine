#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATION_SET_H
#define INCLUDED_VISHV_GRAPHICS_ANIMATION_SET_H

#include "AnimationClip.h"

namespace Vishv::Graphics
{
	struct AnimationSet
	{
		std::vector<std::unique_ptr<AnimationClip>> animationClips;

		float blendTimer = 1.0f;

		size_t GetIndex(std::string name)
		{
			for (size_t i = 0; i < animationClips.size(); ++i)
			{
				if (animationClips[i]->name == name)
				{
					return i;
				}
			}
			return 0;
		}

		AnimationClip* GetAnimation(std::string name)
		{
			for (size_t i = 0; i < animationClips.size(); ++i)
			{
				if (animationClips[i]->name == name)
				{
					return animationClips[i].get();
				}
			}
			return nullptr;
		}
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_ANIMATION_SET_H

