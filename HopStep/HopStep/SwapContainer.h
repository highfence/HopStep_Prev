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

		inline T& GetOutRef() const { return m_OutReference; }
		inline T& GetInRef() const { return m_InReference; }
		void Swap();

	private :

		std::mutex m_SwapMutex;

		T* m_FirstContainer = nullptr;
		T* m_SecondContrainer = nullptr;

		T& m_OutReference;
		T& m_InReference;
	};

	template<class T>
	inline SwapContainer<T>::SwapContainer(T* firstContainer, T* secondContainer)
	{
		if (firstContainer == nullptr || secondContainer == nullptr)
			return;

		m_FirstContainer = firstContainer;
		m_SecondContrainer = secondContainer;

		m_InReference = m_FirstContainer;
		m_OutReference = m_SecondContrainer;
	}

	template<class T>
	inline SwapContainer<T>::~SwapContainer()
	{
	}

	template<class T>
	inline void SwapContainer<T>::Swap()
	{
		std::lock_guard<std::mutex> releaseLock(m_SwapMutex);

		if (m_OutReference == m_FirstContainer && m_InReference == m_SecondContrainer)
		{
			m_InReference = m_FirstContainer;
			m_OutReference = m_SecondContrainer;
		}
		else if (m_OutReference == m_SecondContrainer && m_InReference == m_FirstContainer)
		{
			m_InReference = m_SecondContrainer;
			m_OutReference = m_FirstContainer;
		}
	}
}