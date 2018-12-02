#include "stdafx.h"
#include "IDGenerator.h"


namespace HopStep
{
	std::shared_ptr<IDGenerator> IDGenerator::instance = nullptr;
	std::atomic<long long> IDGenerator::idCount = 0L;

	std::shared_ptr<IDGenerator> IDGenerator::Get()
	{
		if (instance == nullptr)
		{
			instance = std::make_shared<IDGenerator>();
		}
		return instance;
	}

	long long IDGenerator::GetID()
	{
		++idCount;
		return idCount;
	}
}
