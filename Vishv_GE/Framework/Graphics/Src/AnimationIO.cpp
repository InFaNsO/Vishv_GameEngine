#include "Precompiled.h"
#include "AnimationIO.h"
//#include "AnimationClip.h"
#include "Keyframe.h"

using namespace Vishv;
using namespace Vishv::Math;
using namespace Vishv::Graphics;

bool Vishv::Graphics::AnimationIO::SaveAnimations(std::vector<std::unique_ptr<AnimationClip>>& animations, std::string meshName)
{
	std::filesystem::path filePath = rootPath.string() + meshName;

	for (uint32_t index = 0; index < animations.size(); ++index)
	{
		if (!SaveAnimation(*animations[index].get(), filePath.string() + (animations[index]->name + ".vanim") ))
			return false;
	}
	return true;
}

bool Vishv::Graphics::AnimationIO::SaveAnimation(AnimationClip & animation, std::filesystem::path path)
{
	std::fstream file;
	file.open(path, std::ios::out | std::ios::app);
	file.close();
	file.open(path);
	if (!file.is_open())
		return false;
	file.clear();

	file << "Name: " << animation.name << "\n";
	file << "Duration: " << animation.duration << "\n";
	file << "TicksPerSec: " << animation.ticksPerSecond << "\n";
	file << "BoneNums: " << animation.boneAnimations.size() << "\n";

	for (size_t i = 0; i < animation.boneAnimations.size(); ++i)
	{
		if (animation.boneAnimations[i] == nullptr)
		{
			file << "BoneName: null" << "\n";
			file << "BoneIndex: -1" << "\n";
			file << "PosKey: 0" << "\n";
			file << "RotKey: 0" << "\n";
			file << "ScaleKey: 0" << "\n";
		}
		else
		{
			file << "BoneName: " << animation.boneAnimations[i]->name << "\n";
			file << "BoneIndex: " << std::to_string(i) << "\n";

			auto& posKeys = animation.boneAnimations[i]->animation.GetPositionKeys();
			auto& rotKeys = animation.boneAnimations[i]->animation.GetRotationKeys();
			auto& scaleKeys = animation.boneAnimations[i]->animation.GetScaleKeys();


			file << "PosKeyNum: " << posKeys.size() << "\n";
			for (size_t j = 0; j < posKeys.size(); ++j)
			{
				file << posKeys[j].value.ToString() << " " << posKeys[j].time << " " << (int)posKeys[j].easing << "\n";
			}
			file << "RotKeyNum: " << rotKeys.size() << "\n";
			for (size_t j = 0; j < rotKeys.size(); ++j)
			{
				file << rotKeys[j].value.ToString() << " " << rotKeys[j].time << " " << (int)rotKeys[j].easing << "\n";
			}
			file << "ScaleKeyNum: " << scaleKeys.size() << "\n";
			for (size_t j = 0; j < scaleKeys.size(); ++j)
			{
				file << scaleKeys[j].value.ToString() << " " << scaleKeys[j].time << " " << (int)scaleKeys[j].easing << "\n";
			}
		}
	}
	file.close();
	return true;
}

bool Vishv::Graphics::AnimationIO::LoadAnimation(std::string name, AnimationClip & clip)
{
	std::filesystem::path filePath = rootPath / name;
	filePath /= name + ".vskel";

	return LoadAnimation(filePath, clip);
}

bool Vishv::Graphics::AnimationIO::LoadAnimation(std::filesystem::path filePath, AnimationClip& clip)
{
	std::fstream file;
	file.open(filePath);

	//VISHVASSERT(!file.is_open(), "[SkeletonIO] Error wrong file name sent or the file doesn't exist in the 3d models folder");

	if (!file.is_open())
		return false;
	std::string holder;
	int numBones;
	file >> holder >> clip.name >> holder >> clip.duration >> holder >> clip.ticksPerSecond >> holder >> numBones;

	clip.boneAnimations.reserve(numBones);
	for (size_t i = 0; i <(size_t) numBones; ++i)
	{
		auto& anim = clip.boneAnimations.emplace_back(std::make_unique<BoneAnimation>());
		int size = 0;
		file >> holder >> anim->name >> holder >> anim->index >> holder >> size;
		auto& posKey = anim->animation.GetPositionKeys();
		auto& rotKey = anim->animation.GetRotationKeys();
		auto& scaleKey = anim->animation.GetScaleKeys();

		posKey.reserve(size);
		for (int i = 0; i < size; ++i)
		{
			PositionKeyframe pk;
			int ease;
			file >> pk.value.x >> pk.value.y >> pk.value.z >> pk.time >> ease;

			pk.easing = (EasingType)ease;
			posKey.emplace_back(pk);
		}

		file >> holder >> size;
		rotKey.reserve(size);
		for (int i = 0; i < size; ++i)
		{
			RotationKeyframe rk;
			int ease;
			file >> rk.value.w >> rk.value.x >> rk.value.y >> rk.value.z >> rk.time >> ease;

			rk.easing = (EasingType)ease;
			rotKey.emplace_back(rk);
		}

		file >> holder >> size;
		scaleKey.reserve(size);
		for (int i = 0; i < size; ++i)
		{
			ScaleKeyframe sk;
			int ease;
			file >> sk.value.x >> sk.value.y >> sk.value.z >> sk.time >> ease;

			sk.easing = (EasingType)ease;
			scaleKey.emplace_back(sk);
		}

		if (anim->name == "null")
			anim.reset();
	}
	file.close();

	return true;
}


bool Vishv::Graphics::AnimationIO::LoadAnimationMingzhou(std::filesystem::path filePath, AnimationClip & skeleton)
{
	std::fstream file;
	file.open(filePath);

	return false;
}
