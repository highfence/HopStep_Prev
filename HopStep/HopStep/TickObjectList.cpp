#include "stdafx.h"
#include "TickObject.h"
#include "TickObjectList.h"

namespace HopStep
{
	std::shared_ptr<TickObjectList> TickObjectList::instance = nullptr;

	std::shared_ptr<TickObjectList> Internal::TickObjectList::Get()
	{
		if (instance == nullptr)
			instance = std::make_shared<TickObjectList>();
		
		return instance;
	}

	Internal::TickObjectList::~TickObjectList()
	{
		instance = nullptr;

		m_TickObjects.clear();
	}

	Result Internal::TickObjectList::AddObject(TickObject * object)
	{
		if (object == nullptr)
			return Result::NullParameter;

		if (std::find(m_TickObjects.begin(), m_TickObjects.end(), object) != m_TickObjects.end())
			return Result::DuplicatedObject;

		m_TickObjects.push_back(object);

		return Result::None;
	}

	Result Internal::TickObjectList::DeleteObject(TickObject * object)
	{
		if (object == nullptr)
			return Result::NullParameter;

		std::remove(m_TickObjects.begin(), m_TickObjects.end(), object);

		return Result::None;
	}

	void Internal::TickObjectList::ProcessTick(const float deltaTime)
	{
		for (const auto& tickObject : m_TickObjects)
		{
			if (tickObject == nullptr)
				continue;

			tickObject->Tick(deltaTime);
		}
	}
}
