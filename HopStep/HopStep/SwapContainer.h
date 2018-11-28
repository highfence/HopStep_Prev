#pragma once
#include <mutex>

namespace HopStep
{
	template<class T>
	class SwapContainer
	{
	public :

		SwapContainer(T* firstContainer, T* secondContainer);
		~SwapContainer();

		inline T& GetContainer() const { return m_OutReference; }
		void Swap();

	private :

		std::mutex m_SwapMutex;

		T* m_FirstContainer = nullptr;
		T* m_SecondContrainer = nullptr;

		T& m_OutReference;
	};

	template<class T>
	inline SwapContainer<T>::SwapContainer(T* firstContainer, T* secondContainer)
	{
		if (firstContainer == nullptr || secondContainer == nullptr)
			return;

		m_FirstContainer = firstContainer;
		m_SecondContrainer = secondContainer;

		m_OutReference = m_FirstContainer;
	}

	template<class T>
	inline SwapContainer<T>::~SwapContainer()
	{
	}

	template<class T>
	inline void SwapContainer<T>::Swap()
	{
		std::lock_guard<std::mutex> releaseLock(m_SwapMutex);

		if (m_OutReference == m_FirstContainer)
		{
			m_OutReference = m_SecondContrainer;
		}
		else if (m_OutReference == m_SecondContrainer)
		{
			m_OutReference = m_FirstContainer;
		}
	}
}