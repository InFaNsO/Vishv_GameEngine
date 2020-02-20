#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATION
#define INCLUDED_VISHV_GRAPHICS_ANIMATION

#include "Common.h"
#include "Keyframe.h"

namespace Vishv::Graphics
{
class Animation
{
public:
	Animation() = default;
	Animation(PositionKeys transform, ScaleKeys scale, RotationKeys rot)
		: mKeyframeTranslation(std::move(transform))
		, mKeyframeScale(std::move(scale))
		, mKeyframeRotation(std::move(rot))
	{
	}

	Vishv::Math::Matrix4 GetTransformation(float time);
	void GetTransformation(float time, Math::Vector3& position, Math::Quaternion& rotation);

	void SetLooping(bool loop) { mIsLooping = loop;}
	bool IsLooping() { return mIsLooping; }

	template<class T>
	int GetClosest(std::vector<Keyframe<T>> & keys, float t)
	{
		int i = -1;
		for (auto& key : keys)
		{
			if (key.time > t)
				break;
			i++;
		}
		return i;
	}

	template<class T>
	int GetNext(std::vector<Keyframe<T>> & keys, float t)
	{
		int i = -1;
		for (auto& key : keys)
		{
			i++;
			if (key.time > t)
				break;
		}
		if (i == keys.size())
		{
			if (mIsLooping)
				i = 0;
			else
				i -= 1;
		}
		return i;
	}

	PositionKeys& GetPositionKeys() { return mKeyframeTranslation; }
	RotationKeys& GetRotationKeys() { return mKeyframeRotation; }
	ScaleKeys& GetScaleKeys() { return mKeyframeScale; }

private:
	bool mIsLooping = false;

	PositionKeys mKeyframeTranslation;
	ScaleKeys mKeyframeScale;
	RotationKeys mKeyframeRotation;
};

class BoneAnimation
{
public:
	std::string name;
	int index;
	Animation animation;
};

using BoneAnimations = std::vector<std::unique_ptr<BoneAnimation>>;
}

#endif // !INCLUDED_VISHV_GRAPHICS_ANIMATION
