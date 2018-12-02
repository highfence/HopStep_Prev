#pragma once
#include <memory>
#include <atomic>

namespace HopStep
{
	// Todo : Thread safe for Get method
	class IDGenerator
	{
	public:

		IDGenerator() = delete;
		~IDGenerator() { instance == nullptr; }

		static std::shared_ptr<IDGenerator> Get();
		long long GetID();

	private :

		static std::shared_ptr<IDGenerator> instance;
		static std::atomic<long long> idCount;

	};
}
