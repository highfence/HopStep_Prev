#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		class GameTimer
		{
		public:

			GameTimer();
			virtual ~GameTimer();

			void InitTimer();
			void ProcessTime();

			inline float GetElapsedTime() const
			{
				return m_ElapsedTime;
			}

		private:

			bool m_UseQPF;
			float m_ElapsedTime;
			LONGLONG m_QPFTicksPerSec;
			LONGLONG m_LastElapsedTime;
		};
	}
}
