#include "stdafx.h"
#include "Timer.h"

namespace HopStep
{
	GameTimer::GameTimer()
		: m_UseQPF(false), m_ElapsedTime(0.f), m_QPFTicksPerSec(0), m_LastElapsedTime(0)
	{
	}

	GameTimer::~GameTimer()
	{
	}

	void GameTimer::InitTimer()
	{
		LARGE_INTEGER qwTicksPerSec, qwTime;

		m_UseQPF = (bool)(QueryPerformanceFrequency(&qwTicksPerSec) != 0);

		if (m_UseQPF == false)
			return;

		m_QPFTicksPerSec = qwTicksPerSec.QuadPart;

		QueryPerformanceCounter(&qwTime);
		m_LastElapsedTime = qwTime.QuadPart;
	}

	void GameTimer::ProcessTime()
	{
		if (m_UseQPF == false)
			return;

		LARGE_INTEGER qwTime;
		QueryPerformanceCounter(&qwTime);

		m_ElapsedTime = (float)((double)(qwTime.QuadPart - m_LastElapsedTime) / (double)m_QPFTicksPerSec);
		m_LastElapsedTime = qwTime.QuadPart;
	}
}
