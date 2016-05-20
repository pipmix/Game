#include "Timer.h"

Timer::Timer() {
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	m_ticksPerMs = (float)(m_frequency / 1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
}
Timer::~Timer() {}
void Timer::Update() {
	INT64 currentTime;
	float timeDifference;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	timeDifference = (float)(currentTime - m_startTime);
	m_frameTime = timeDifference / m_ticksPerMs;
	m_startTime = currentTime;
}
float Timer::GetDelta() { return m_frameTime; }