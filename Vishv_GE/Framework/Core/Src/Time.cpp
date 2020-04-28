#include "Precompiled.h"
#include "Time.h"

#include "Debug.h"

namespace
{
	std::unique_ptr<Vishv::Core::Time> sInstance = nullptr;
}

using namespace Vishv;

void Vishv::Core::Time::StaticInitialize()
{
	VISHVASSERT(sInstance == nullptr, "[Time] already Initialized");
	sInstance = std::make_unique<Time>();
	sInstance->Initialize();
}

void Vishv::Core::Time::StaticTerminate()
{
	if (sInstance != nullptr)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}

Vishv::Core::Time* Vishv::Core::Time::Get()
{
	VISHVASSERT(sInstance != nullptr, "[Time] not Initialized");
	return sInstance.get();
}

void Vishv::Core::Time::Initialize()
{
	prvTimePoint = std::chrono::system_clock::now();
}

void Vishv::Core::Time::Terminate()
{
}


void Vishv::Core::Time::Update()
{
	std::chrono::duration<float> diff = std::chrono::system_clock::now() - prvTimePoint;
	mUnscaledDeltaTime = diff.count();
	mUnscaledTime += mUnscaledDeltaTime;

	mDeltaTime = mUnscaledDeltaTime * mTimeScale;
	mTime += mDeltaTime;

	mFrameCount++;
	mFpS = static_cast<int>(1.0f / mUnscaledDeltaTime);

	prvTimePoint = std::chrono::system_clock::now(); 
}

void Vishv::Core::Time::SetScale(float scale)
{
	VISHVASSERT(scale >= 0.0f, "[Time] The Scale cannot be negative");
	mTimeScale = scale;
}
