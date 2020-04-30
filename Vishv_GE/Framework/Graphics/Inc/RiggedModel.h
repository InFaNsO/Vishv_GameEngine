#ifndef INCLUDED_VISHV_GRAPHICS_RIGGED_MODEL_H
#define INCLUDED_VISHV_GRAPHICS_RIGGED_MODEL_H

#include "Model.h"
#include "Skeleton.h"

namespace Vishv::Graphics
{
	struct RiggedModel
	{
		Model model;
		Skeleton skeleton;

		std::vector<Vishv::Math::Matrix4> mTPosToParent;
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_RIGGED_MODEL_H


