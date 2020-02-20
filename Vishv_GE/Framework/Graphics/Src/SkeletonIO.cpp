#include "Precompiled.h"
#include "SkeletonIO.h"
#include "Skeleton.h"

using namespace Vishv;
using namespace Vishv::Math;
using namespace Vishv::Graphics;


namespace
{
	void MakeString(Bone & b, std::string & txt)
	{
		txt = "";

		txt += b.name + " ";
		txt += std::to_string(b.index) + " ";
		if (b.parent == nullptr)
			txt += std::to_string(-1) + " ";
		else
			txt += std::to_string(b.parent->index) + " ";
		txt += std::to_string(b.children.size()) + " ";

		for (uint32_t i = 0; i < b.children.size(); ++i)
		{
			txt += std::to_string(b.children[i]->index) + " ";
		}

		txt += b.toParentTransform.To_String();
		txt += b.offsetTransform.To_String();
		txt += "\n";
	}
}


bool Vishv::Graphics::SkeletonIO::SaveSkeleton(Skeleton & skeleton, std::string name)
{
	std::filesystem::path filePath = rootPath / name;
	filePath /= "_Mesh.vskel";

	return SaveSkeleton(skeleton, filePath);
}

bool Vishv::Graphics::SkeletonIO::SaveSkeleton(Skeleton & skeleton, std::filesystem::path path)
{
	std::fstream file;
	file.open(path, std::ios::out | std::ios::app);
	file.close();
	file.open(path);
	if (!file.is_open())
		return false;
	file.clear();

	file << "NumberBones " << skeleton.bones.size() << std::endl;
	file << "RootBoneID " << skeleton.root->index << std::endl;

	std::string text = "";
	for (uint32_t i = 0; i < skeleton.bones.size(); ++i)
	{
		MakeString(*skeleton.bones[i].get(), text);
		file << text;
	}

	/*
	things to save
	number of bones
	root bone index (id)

	bone index (id)
	parent index (p id)
	children indecies (c ids)

	matrix4 to parent
	matrix4 offset
	*/

	file.close();
	return true;
}

void Vishv::Graphics::SkeletonIO::Connect(Skeleton & skeleton)
{
	for (uint32_t i = 0; i < skeleton.bones.size(); ++i)
	{
		if(skeleton.bones[i].get()->parentId != -1)
			skeleton.bones[i].get()->parent = skeleton.bones[skeleton.bones[i].get()->parentId].get();
		skeleton.bones[i].get()->children.resize(skeleton.bones[i].get()->childIndicies.size());

		for (uint32_t j = 0; j < skeleton.bones[i].get()->childIndicies.size(); ++j)
		{
			skeleton.bones[i].get()->children[j] = skeleton.bones[skeleton.bones[i].get()->childIndicies[j]].get();
		}
	}
}

bool Vishv::Graphics::SkeletonIO::LoadSkeleton(std::string name, Skeleton & skeleton)
{
	std::filesystem::path filePath = rootPath / name;
	filePath /= name + "_Mesh.vskel";

	return LoadSkeleton(filePath, skeleton);
}

bool Vishv::Graphics::SkeletonIO::LoadSkeleton(std::filesystem::path filePath, Skeleton & skeleton)
{
	std::fstream file;
	file.open(filePath);

	if (!file.is_open())
		return false;


	/*
	order of file
	number of bones
	root bone index (id)

	bone index (id)
	parent index (p id)
	children indecies (c ids)

	matrix4 to parent
	matrix4 offset
	*/

	uint32_t numBones, rootId;
	std::string holder;

	file >> holder >> numBones;
	skeleton.bones.reserve(numBones);

	file >> holder >> rootId;

	for (uint32_t i = 0; i < numBones; ++i)
	{
		std::unique_ptr<Bone> bone = std::make_unique<Bone>();
		file >> bone->name;
		file >> bone->index;
		file >> bone->parentId;
		uint32_t numberKids;
		file >> numberKids;
		bone->childIndicies.reserve(numberKids);

		for (uint32_t cI = 0; cI < numberKids; ++cI)
		{
			uint32_t id;
			file >> id;
			bone->childIndicies.emplace_back(id);
		}

		std::array<float, 16> mat;
		float val;
		for (uint32_t mI = 0; mI < 16; ++mI)
		{
			file >> val;
			mat[mI] = val;
		}
		bone->toParentTransform = mat;
		for (uint32_t mI = 0; mI < 16; ++mI)
		{
			file >> val;
			mat[mI] = val;
		}
		bone->offsetTransform = mat;

		skeleton.bones.emplace_back(std::move(bone));
	}

	file.close();

	skeleton.root = skeleton.bones[rootId].get();
	skeleton.root->parent = nullptr;

	Connect(skeleton);

	return true;
}

