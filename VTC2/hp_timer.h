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

public:
	HPTimer() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequency = t.QuadPart;

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

			timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度はガタガタ)
			Sleep(sleepTime);   // 寝る
			timeEndPeriod(1);   // 戻す
		}
	}
};