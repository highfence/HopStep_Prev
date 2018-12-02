#include "stdafx.h"
#include "ObjectManager.h"

namespace HopStep
{
	std::shared_ptr<ObjectManager> ObjectManager::instance = nullptr;

	std::shared_ptr<ObjectManager> ObjectManager::Get()
	{
		if (instance == nullptr)
		{
			instance = std::make_shared<ObjectManager>();
		}
		return instance;
	}
}
