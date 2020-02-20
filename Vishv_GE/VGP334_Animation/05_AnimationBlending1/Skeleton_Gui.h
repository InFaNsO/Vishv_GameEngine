#pragma once
#include "Vishv/Inc/Vishv.h"


namespace Vishv::UI
{
	class SkeletonUI
	{
	public:
		uint32_t GetDepth();
		void SetBoneDebugColour(Vishv::Graphics::Color& shallowColor, Vishv::Graphics::Color& deepColor);
		void ShowBoneHirarchy();
		void SetSkeleton(Vishv::Graphics::Skeleton& skeleton) { mSkeleton = &skeleton; }

	private:
		uint32_t getDepth(Vishv::Graphics::Bone* bone);
		void setDebugColor(Vishv::Graphics::Bone* bone, uint32_t currentDepth, uint32_t totalDepth);

		void WriteBoneNameAndCallChildren(Vishv::Graphics::Bone* bone);

		Graphics::Color shallowC;
		Graphics::Color deepC;

		Vishv::Graphics::Skeleton* mSkeleton;
	};
}

