#ifndef INCLUDED_VISHV_GRAPHICS_KEYFRAME
#define INCLUDED_VISHV_GRAPHICS_KEYFRAME

#include "Common.h"
#include "AnimationEasing.h"

namespace Vishv::Graphics
{
	template<class T>
	struct Keyframe
	{
		T value;
		float time = -1.0f;
		EasingType easing = EasingType::none;


		Keyframe() = default;
		Keyframe(T v, float t) : value(v), time(t) {}
		Keyframe(T v, float t, EasingType ty) : value(v), time(t), easing(ty) {}


		bool operator>(const Keyframe<T>& key)
		{
			return time > key.time;
		}
		bool operator<(const Keyframe<T>& key)
		{
			return time < key.time;
		}
	};

	using PositionKeyframe = Keyframe<Math::Vector3>;
	using ScaleKeyframe = Keyframe<Math::Vector3>;
	using RotationKeyframe = Keyframe<Math::Quaternion>;

	template<class T>
	using Keyframes = std::vector<Keyframe<T>>;

	using PositionKeys = Keyframes<Math::Vector3>;
	using ScaleKeys = Keyframes<Math::Vector3>;
	using RotationKeys = Keyframes<Math::Quaternion>;
}

#endif // !INCLUDED_VISHV_GRAPHICS_KEYFRAME
