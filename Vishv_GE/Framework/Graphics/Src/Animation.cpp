#include "Precompiled.h"
#include "Animation.h"
#include "AnimationEasing.h"

using namespace Vishv;
using namespace Vishv::Graphics;
using namespace Vishv::Math;

namespace
{
	template <class T>
	using LerpFunc = std::function<T(const T&, const T&, float)>;

	template <class T>
	T GetValueAtTime(const Keyframes<T>& keyframes, float time, LerpFunc<T> InterpolateFunc)
	{
		for (size_t i = 0; i + 1 < keyframes.size(); ++i)
		{
			if ((time >= keyframes[i].time) && (time < keyframes[i + 1].time))
			{
				float timepass = time - keyframes[i].time;
				float keyframeDuration = keyframes[i + 1].time - keyframes[i].time;
				float ratio = timepass / keyframeDuration;
				return InterpolateFunc(keyframes[i].value, keyframes[i + 1].value, ratio);
			}
		}

		return T();
	}
}

Vishv::Math::Matrix4 Vishv::Graphics::Animation::GetTransformation(float time)
{
	//make a scale matrix
	Vector3 scale;
	scale = { 1.0f, 1.0f, 1.0f };
	
	//make a transform matrix
	Vector3 translation = GetValueAtTime<Vector3>(mKeyframeTranslation, time, Vector3::Lerp);
	if (translation == Vector3() && mKeyframeTranslation.size() == 1)
		translation = mKeyframeTranslation[0].value;

	//make a rotation matrix and use slerp
	Quaternion rotation = GetValueAtTime<Quaternion>(mKeyframeRotation, time, Quaternion::Slerp);
	if (rotation == Quaternion() && mKeyframeRotation.size() == 1)
		rotation = mKeyframeRotation[0].value;
	
	return Matrix4::TranslationMatrix(rotation, translation); //Vishv::Math::Matrix4::RotateMatrix(rotation) * Vishv::Math::Matrix4::TranslateMatrix(translation);
}

void Vishv::Graphics::Animation::GetTransformation(float time, Math::Vector3 & position, Math::Quaternion & rotation)
{
	//make a scale matrix
	Vector3 scale;
	scale = { 1.0f, 1.0f, 1.0f };

	//make a transform matrix
	Vector3 translation = GetValueAtTime<Vector3>(mKeyframeTranslation, time, Vector3::Lerp);
	if (translation == Vector3() && mKeyframeTranslation.size() == 1)
		translation = mKeyframeTranslation[0].value;

	//make a rotation matrix and use slerp
	Quaternion rot = GetValueAtTime<Quaternion>(mKeyframeRotation, time, Quaternion::Slerp);
	if (rot == Quaternion() && mKeyframeRotation.size() == 1)
		rot = mKeyframeRotation[0].value;

	position = translation;
	rotation = rot;
}

