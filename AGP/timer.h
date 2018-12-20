#pragma once
#include <windows.h>
class timer
{
public:
	timer();
	~timer();

	float gameTime() const;
	float deltaTime() const;

	void reset();
	void start();
	void stop();
	void tick();

	float getCurrentTime();

private:

	double mSecondsPerCount;
	double mDeltaTime;

	float mBaseTime;
	float mPausedTime;
	float mStopTime;
	float mPrevTime;
	float mCurrTime;

	bool mStopped;

};

