#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace Vishv;
using namespace Vishv::Graphics;
using namespace Vishv::Math;

AnimationBuilder & Vishv::Graphics::AnimationBuilder::AddPositionKey(PositionKeyframe key)
{
	//if(mPositionKeys.empty())
		mPositionKeys.push_back(key);
	//else
	//{
	//	auto itPrv = mPositionKeys.begin();
	//	for (auto iter = mPositionKeys.begin(); iter != mPositionKeys.end(); ++iter)
	//	{
	//		if (*iter > key)
	//		{
	//			mPositionKeys.insert(itPrv, key);
	//			break;
	//		}
	//
	//		if (iter != mPositionKeys.begin())
	//			itPrv++;
	//	}
	//}
	return *this;
}

AnimationBuilder & Vishv::Graphics::AnimationBuilder::AddScaleKey(ScaleKeyframe key)
{
	//if (mScaleKeys.empty())
		mScaleKeys.push_back(key);
	//else
	//{
	//	auto itPrv = mScaleKeys.begin();
	//	for (auto iter = mScaleKeys.begin(); iter != mScaleKeys.end(); ++iter)
	//	{
	//		if (*iter > key)
	//		{
	//			mScaleKeys.insert(itPrv, key);
	//			break;
	//		}
	//
	//		if (iter != mScaleKeys.begin())
	//			itPrv++;
	//	}
	//}
	return *this;
}

AnimationBuilder & Vishv::Graphics::AnimationBuilder::AddRotationKey(RotationKeyframe key)
{
	//if (mRotationKeys.empty())
		mRotationKeys.push_back(key);
	//else
	//{
	//	auto itPrv = mRotationKeys.begin();
	//	for (auto iter = mRotationKeys.begin(); iter != mRotationKeys.end(); ++iter)
	//	{
	//		if (*iter > key)
	//		{
	//			mRotationKeys.insert(itPrv, key);
	//			break;
	//		}
	//
	//		if (iter != mRotationKeys.begin())
	//			itPrv++;
	//	}
	//}
	return *this;
}

Animation Vishv::Graphics::AnimationBuilder::Build()
{
	return Animation(std::move(mPositionKeys), std::move(mScaleKeys), std::move(mRotationKeys));
}
