#include "stdafx.h"
#include "Timer.h"

namespace HopStep
{
	Timer::Timer()
		: m_UseQPF(false), m_ElapsedTime(0.f), m_QPFTicksPerSec(0), m_LastElapsedTime(0)
	{
	}

	Timer::~Timer()
	{
	}

	void Timer::InitTimer()
	{
		LARGE_INTEGER qwTicksPerSec, qwTime;

		m_UseQPF = (bool)(QueryPerformanceFrequency(&qwTicksPerSec) != 0);

		if (m_UseQPF == false)
			return;

		m_QPFTicksPerSec = qwTicksPerSec.QuadPart;

		QueryPerformanceCounter(&qwTime);
		m_LastElapsedTime = qwTime.QuadPart;
	}

	void Timer::ProcessTime()
	{
		if (m_UseQPF == false)
			return;

		LARGE_INTEGER qwTime;
		QueryPerformanceCounter(&qwTime);

		m_ElapsedTime = (float)((double)(qwTime.QuadPart - m_LastElapsedTime) / (double)m_QPFTicksPerSec);
		m_LastElapsedTime = qwTime.QuadPart;
	}
}
