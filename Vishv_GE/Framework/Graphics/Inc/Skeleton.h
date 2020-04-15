#ifndef INCLUDED_VISHV_GRAPHICS_SKELETON_H
#define INCLUDED_VISHV_GRAPHICS_SKELETON_H

#include "Bone.h"

namespace Vishv::Graphics
{
class Skeleton
{
public:			//My skeleton
	Skeleton() = default;
	void AddBone();
	Bone* CreateBone(int parentID);
	Bone* GetBone();
	Bone* GetBone(std::string name);
	Bone* GetBone(int id);
	std::vector<std::unique_ptr<Bone>>& GetBoneArray() { return bones; }
	void Update();
	void SetOffsetMat(size_t boneID, Math::Matrix4& offset);
	void SetOffsetMat(size_t boneID, Math::Transform& offset);

	Math::Matrix4 GetTransformation(size_t boneId);

	static size_t MaxBoneCount() { return 256; }

public:				//class skeleton
	Bone* root = nullptr;
	std::vector<std::unique_ptr<Bone>> bones;

};
}

#endif // !INCLUDED_VISHV_GRAPHICS_SKELETON_H

