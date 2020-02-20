#ifndef INCLUDED_VISHV_GRAPHICS_RIGGED_MODEL_H
#define INCLUDED_VISHV_GRAPHICS_RIGGED_MODEL_H

#include "Model.h"
#include "Skeleton.h"
#include "AnimationSet.h"
#include "AnimationPlayInformation.h"

namespace Vishv::Graphics
{
	struct RiggedModel
	{
		Model model;
		Skeleton skeleton;

		AnimationSet* animations;

		std::vector<AnimationPlayInformation> playAnimations;
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_RIGGED_MODEL_H


