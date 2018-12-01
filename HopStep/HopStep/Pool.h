#pragma once
#include <mutex>

namespace HopStep
{
	template<class T>
	class Pool
	{
	public:

		Pool() {};
		~Pool() { Release(); };

		void Init(const int poolSize);
		void Release();

		int GetTag();
		void ReleaseTag(const int tag);

		int GetSize();
		int GetActivatedObjectCount() const { return m_ActivatedObjectCount; }
		bool IsEmpty();

		T& begin();
		T& end();
		T& operator[](const int idx);

	private:

		bool m_IsInitialized = false;
		int m_ActivatedObjectCount = 0;

		std::mutex m_PoolMutex;
		std::vector<std::unique_ptr<T>> m_Pool;
		std::deque<int> m_PoolIndex;
	};

	// ������Ʈ Ǯ �������� ũ�⸦ �̿��Ͽ� �ʱ�ȭ�� ���־�� �Ѵ�.
	template<class T>
	inline void Pool<T>::Init(const int poolSize)
	{
		m_Pool.reserve(poolSize);

		for (auto i = 0; i < poolSize; ++i)
		{
			m_Pool.emplace_back(std::make_unique<T>());
			m_PoolIndex.push_back(i);
		}

		m_IsInitialized = true;
	}

	template<class T>
	inline void Pool<T>::Release()
	{
		m_IsInitialized = false;

		std::lock_guard<std::mutex> releaseLock(m_PoolMutex);
		m_Pool.clear();
		m_Pool.shrink_to_fit();

		m_PoolIndex.clear();
		m_PoolIndex.shrink_to_fit();
	}

	template<class T>
	inline int Pool<T>::GetTag()
	{
		if (!m_IsInitialized) return -1;

		std::lock_guard<std::mutex> tagLock(m_PoolMutex);
		if (m_PoolIndex.empty())
		{
			return -1;
		}

		auto returnTag = m_PoolIndex.front();
		m_PoolIndex.pop_front();

		++m_ActivatedObjectCount;

		return returnTag;
	}

	template<class T>
	inline void Pool<T>::ReleaseTag(const int tag)
	{
		if (!m_IsInitialized) return;

		std::lock_guard<std::mutex> tagLock(m_PoolMutex);
		m_PoolIndex.push_back(tag);

		--m_ActivatedObjectCount;
	}

	template<class T>
	inline int Pool<T>::GetSize()
	{
		if (!m_IsInitialized) return -1;

		std::lock_guard<std::mutex> sizeLock(m_PoolMutex);
		return static_cast<int>(m_Pool.size());
	}

	template<class T>
	inline T & Pool<T>::begin()
	{
		if (!m_IsInitialized) return -1;

		std::lock_guard<std::mutex> poolLock(m_PoolMutex);
		return m_Pool.begin();
	}

	template<class T>
	inline T & Pool<T>::end()
	{
		if (!m_IsInitialized) return -1;

		std::lock_guard<std::mutex> poolLock(m_PoolMutex);
		return m_Pool.end();
	}

	template<class T>
	inline T & Pool<T>::operator[](const int idx)
	{
		std::lock_guard<std::mutex> poolLock(m_PoolMutex);
		return *m_Pool[idx];
	}

	template<class T>
	inline bool Pool<T>::IsEmpty()
	{
		if (!m_IsInitialized) return true;

		std::lock_guard<std::mutex> poolLock(m_PoolMutex);
		return m_Pool.empty();
	}
}
