#include "Skeleton_Gui.h"

using namespace Vishv;
using namespace Vishv::UI;

uint32_t Vishv::UI::SkeletonUI::GetDepth()
{
}

uint32_t Vishv::UI::SkeletonUI::getDepth(Vishv::Graphics::Bone * bone)
{
	std::vector<int> depth;

	for (size_t i = 0; i < bone->children.size(); ++i)
	{
		//call the depth function on each and compare the size
		depth.push_back((uint32_t)getDepth(bone->children[i]));
	}

	int deepest = 0;
	for (size_t i = 0; i < depth.size(); ++i)
	{
		if (depth[i] > deepest)
			deepest = depth[i];
	}

	return deepest + 1;
}

void Vishv::UI::SkeletonUI::SetBoneDebugColour(Vishv::Graphics::Color & shallowColor, Vishv::Graphics::Color & deepColor)
{
	shallowC = shallowColor;
	deepC = deepColor;

	setDebugColor(mSkeleton->root, 0, GetDepth());
}

void Vishv::UI::SkeletonUI::setDebugColor(Vishv::Graphics::Bone * bone, uint32_t currentDepth, uint32_t totalDepth)
{
	float ratio = static_cast<float>(currentDepth) / static_cast<float>(totalDepth);
	bone->mDebugColor = Vishv::Math::Vector4::Interpolate(shallowC, deepC, ratio);

	for (size_t i = 0; i < bone->children.size(); ++i)
	{
		setDebugColor(bone->children[i], currentDepth + 1, totalDepth);
	}
}

void Vishv::UI::SkeletonUI::WriteBoneNameAndCallChildren(Vishv::Graphics::Bone * bone)
{
	if(	ImGui::CollapsingHeader(bone->name.c_str()))
		for (size_t i = 0; i < bone->children.size(); ++i)
		{
			WriteBoneNameAndCallChildren(bone->children[i]);
		}
}

void Vishv::UI::SkeletonUI::ShowBoneHirarchy()
{
	ImGui::Begin("Skeleton Bones");

	WriteBoneNameAndCallChildren(mSkeleton->root);

	ImGui::End();

}
