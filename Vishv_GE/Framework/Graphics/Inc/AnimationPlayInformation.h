#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATION_PLAY_INFORMATION_H
#define INCLUDED_VISHV_GRAPHICS_ANIMATION_PLAY_INFORMATION_H

#include "AnimationEasing.h"

namespace Vishv::Graphics
{
	struct AnimationPlayInformation
	{
		int animationIndex = -1;
		float time = 0.0f;
		float maxTime = 1.0f;
		EasingHead mEasingType = EasingHead::none;
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_ANIMATION_PLAY_INFORMATION_H

