#ifndef INCLUDED_VISH_CORE_TIME_H
#define INCLUDED_VISH_CORE_TIME_H

namespace Vishv::Core
{
	class Time
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static Time* Get();

	public:
		void Initialize();
		void Terminate();
		void Update();

		void SetScale(float scale);

		const float& CurrentTime() { return mTime; }
		const float& DeltaTime() { return mDeltaTime; }

		const float& TimeScale() { return mTimeScale; }

		const float& UnscaledDeltaTime() { return mUnscaledDeltaTime; }
		const float& UnscaledTime() { return mUnscaledTime; }

		const int& FpS() { return mFpS; }
		const int& FrameCount() { return mFrameCount; }

	private:
		
		int mFrameCount = 0;
		float mTime = 0.0f;
		float mDeltaTime = 0.33f;
		float mTimeScale = 1.0f;

		float mUnscaledTime = 0.0f;
		float mUnscaledDeltaTime = 0.33f;

		int mFpS = 0;

	};
}

#endif // !INCLUDED_VISH_CORE_TIME_H


