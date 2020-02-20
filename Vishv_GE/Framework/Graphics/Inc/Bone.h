#ifndef INCLUDED_VISHV_GRAPHICS_BONE
#define INCLUDED_VISHV_GRAPHICS_BONE

#include "Common.h"
#include "Animation.h"
#include "Colors.h"

namespace Vishv::Graphics
{
	struct Bone
	{
		std::string name ="";
		int index = -1;

		Bone* parent = nullptr;
		int parentId = -1;

		std::vector<Bone*> children;
		std::vector<int> childIndicies;

		Math::Matrix4 toParentTransform = Vishv::Math::Matrix4::Identity();
		Math::Matrix4 offsetTransform = Vishv::Math::Matrix4::Identity();

		Math::Vector3 posDebug;
		Math::Vector3 rotDebug;

		//debug purpose
		Color mDebugColor = Colors::AliceBlue;
	};
}

#endif
