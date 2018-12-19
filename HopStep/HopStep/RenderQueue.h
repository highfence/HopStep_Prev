#pragma once
#include <memory>
#include <deque>
#include <mutex>

#include "FrameInfo.h"

namespace HopStep
{
	inline namespace Internal
	{
		// Todo : To template class (boost::shared_ptr<T>)
		class RenderQueue
		{
		public:

			RenderQueue() = default;
			~RenderQueue()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				m_FrameQueue.clear();
				m_FrameQueue.shrink_to_fit();
			}

			std::shared_ptr<FrameInfo> Peek()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				if (m_FrameQueue.empty())
					return nullptr;

				return m_FrameQueue.front();
			}

			void Pop()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);

				if (m_FrameQueue.empty() == false)
					m_FrameQueue.pop_front();
			}

			void Push(std::shared_ptr<FrameInfo> frame)
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				m_FrameQueue.push_back(frame);
			}

			bool IsEmpty()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				return m_FrameQueue.empty();
			}

			int Size()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				return m_FrameQueue.size();
			}

			void Clear()
			{
				std::lock_guard<std::mutex> lock(m_Mutex);
				return m_FrameQueue.clear();
			}

		private:

			std::deque<std::shared_ptr<FrameInfo>> m_FrameQueue;
			std::mutex m_Mutex;
		};
	}
}
