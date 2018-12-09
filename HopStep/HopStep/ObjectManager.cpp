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

	Result ObjectManager::RegistObject(GameObject * object)
	{
		if (object == nullptr)
			return Result::NullParameter;

		auto objectPtr = std::make_shared<GameObject>(*object);

		auto idgen = IDGenerator::Get();
		if (idgen == nullptr)
			return Result::GetSingletonFailed;

		ObjectId id = idgen->GetID();
		if (m_ObjectMap.find(id) != m_ObjectMap.end())
			return Result::DuplicatedId;

		objectPtr->SetObjectId(id);

		m_ObjectMap.emplace(id, objectPtr);

		return Result::None;
	}

	Result ObjectManager::ReleaseObject(GameObject * object)
	{
		if (object == nullptr)
			return Result::NullParameter;

		return Result::None;
	}

	Result ObjectManager::ClearAllObject()
	{
		return Result();
	}
}
