#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATION_IO_H
#define INCLUDED_VISHV_GRAPHICS_ANIMATION_IO_H

#include "Common.h"
#include "AnimationClip.h"

namespace Vishv::Graphics
{
	//class AnimationClip;

	class AnimationIO
	{
	public:
		bool SaveAnimations(std::vector<std::unique_ptr<AnimationClip>>& animations, std::string meshName);

		bool SaveAnimation(AnimationClip& animations, std::filesystem::path path);

		bool LoadAnimation(std::string name, AnimationClip& skeleton);
		bool LoadAnimation(std::filesystem::path filePath, AnimationClip& skeleton);

		bool LoadAnimationMingzhou(std::filesystem::path filePath, AnimationClip& skeleton);

		std::filesystem::path rootPath = L"../../Assets/3D_Models/";

	private:
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_SKELETON_IO_H




