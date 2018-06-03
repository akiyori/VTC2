#pragma once

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

class HPTimer {
	const float MIN_FRAME_TIME = 1.0f / 60;
	long long startTime;
	long long lastCallToUpdate;
	long long currentCallToUpdate;
	long long frequency;
	double secondsTimer;
	unsigned int frames = 0;
	
	void UpdateFrameRate() {
		frames++;
		secondsTimer += GetTimeDelta();
		if (secondsTimer > 1) {
			frameRate = (double)frames*0.5 + frameRate*0.5; //more stable
			frames = 0;
			secondsTimer = 0;
		}
	}

public:
	double  frameRate = 30;

	HPTimer() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequency = t.QuadPart;

		secondsTimer = 0;

		Reset();
	}

	void Reset() {
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	} 

	void Update() {
		lastCallToUpdate = currentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;

		UpdateFrameRate();
	}

	double GetTimeTotal() {
		double d = static_cast<double>(currentCallToUpdate - startTime);
		return d / frequency;
	}

	double GetTimeDelta() {
		double d = static_cast<double>(currentCallToUpdate - lastCallToUpdate);
		return d / frequency;
	}

	void WaitFrame() {
		double timeDelta = GetTimeDelta();
		if (timeDelta < MIN_FRAME_TIME) {
			DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - timeDelta) * 1000);

			timeBeginPeriod(1); // ï™âî\Çè„Ç∞ÇÈ(Ç±Ç§ÇµÇ»Ç¢Ç∆SleepÇÃê∏ìxÇÕÉKÉ^ÉKÉ^)
			Sleep(sleepTime);   // êQÇÈ
			timeEndPeriod(1);   // ñﬂÇ∑
		}
	}
};