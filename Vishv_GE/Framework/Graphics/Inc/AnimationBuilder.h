#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATIONBUILDER
#define INCLUDED_VISHV_GRAPHICS_ANIMATIONBUILDER

#include "Common.h"
#include "Keyframe.h"
#include "Animation.h"

namespace Vishv::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& AddPositionKey(PositionKeyframe key);
		AnimationBuilder& AddScaleKey(ScaleKeyframe key);
		AnimationBuilder& AddRotationKey(RotationKeyframe key);

		Animation Build();

	private:
		PositionKeys mPositionKeys;
		ScaleKeys mScaleKeys;
		RotationKeys mRotationKeys;
	};

}
#endif
