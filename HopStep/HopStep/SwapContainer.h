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

		T* GetInContainer();
		T* GetOutContainer();
		void Swap();

	private :

		std::mutex m_SwapMutex;

		T* m_FirstContainer = nullptr;
		T* m_SecondContainer = nullptr;

		bool m_IsFirstIn = true;
	};

	template<class T>
	inline SwapContainer<T>::SwapContainer(T* firstContainer, T* secondContainer)
	{
		if (firstContainer == nullptr || secondContainer == nullptr)
			return;

		m_FirstContainer = firstContainer;
		m_SecondContainer = secondContainer;
	}

	template<class T>
	inline SwapContainer<T>::~SwapContainer()
	{
		delete m_FirstContainer;
		m_FirstContainer = nullptr;
		delete m_SecondContainer;
		m_SecondContainer = nullptr;
	}

	template<class T>
	inline T* SwapContainer<T>::GetInContainer()
	{
		std::lock_guard<std::mutex> releaseLock(m_SwapMutex);

		if (m_IsFirstIn)
			return m_FirstContainer;
		else
			return m_SecondContainer;
	}

	template<class T>
	inline T* SwapContainer<T>::GetOutContainer()
	{
		std::lock_guard<std::mutex> releaseLock(m_SwapMutex);

		if (m_IsFirstIn)
			return m_SecondContainer;
		else
			return m_FirstContainer;
	}

	template<class T>
	inline void SwapContainer<T>::Swap()
	{
		std::lock_guard<std::mutex> releaseLock(m_SwapMutex);

		m_IsFirstIn = !m_IsFirstIn;
	}
}