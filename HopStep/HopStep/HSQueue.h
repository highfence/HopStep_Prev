#pragma once
#include <memory>
#include <deque>
#include <mutex>

namespace HopStep
{
	class HSQueue
	{
	public :

		HSQueue() = default;
		~HSQueue()
		{
			std::lock_guard<std::mutex> lock(m_Mutex);

		}

	private :

		std::deque<std::shared_ptr<T>> m_Deque;
		std::mutex m_Mutex;
	};
}
