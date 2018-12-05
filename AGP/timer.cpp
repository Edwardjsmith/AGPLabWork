#include "timer.h"




timer::timer()
{
	mSecondsPerCount = 0;
	mDeltaTime = -1.0;
	mBaseTime = 0;
	mPausedTime = 0;
	mPrevTime = 0;
	mCurrTime = 0;
	mStopped = false;

	__int64 countsPerSec;

	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;



}


timer::~timer()
{
}

float timer::gameTime() const
{
	return 0.0f;
}

float timer::deltaTime() const
{
	return (float)mDeltaTime;
}

void timer::reset()
{
	__int64 currTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}


void timer::start()
{
	__int64 startTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&startTime);

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void timer::stop()
{
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceFrequency((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void timer::tick()
{
	if (mStopped)
	{
		mDeltaTime = 0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	mPrevTime = mCurrTime;

	if (mDeltaTime < 0)
	{
		mDeltaTime = 0;
	}
}
