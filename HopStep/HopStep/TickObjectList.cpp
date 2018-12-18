#include "stdafx.h"
#include "ITickObject.h"
#include "TickObjectList.h"

namespace HopStep
{
	Internal::TickObjectList::TickObjectList()
	{
		if (thisGameTickObjects != nullptr)
			return;

		thisGameTickObjects = this;
	}

	Internal::TickObjectList::~TickObjectList()
	{
		thisGameTickObjects = nullptr;

		m_TickObjectList.clear();
	}

	Result Internal::TickObjectList::AddObject(ITickObject * object)
	{
		if (object == nullptr)
			return Result::NullParameter;

		if (std::find(m_TickObjectList.begin(), m_TickObjectList.end(), object) == m_TickObjectList.end())
			return Result::DuplicatedObject;

		m_TickObjectList.push_back(object);

		return Result::None;
	}

	Result Internal::TickObjectList::DeleteObject(ITickObject * object)
	{
		if (object == nullptr)
			return Result::NullParameter;

		std::remove(m_TickObjectList.begin(), m_TickObjectList.end(), object);

		return Result::None;
	}

	void Internal::TickObjectList::ProcessTick(const float deltaTime)
	{
		for (const auto& tickObject : m_TickObjectList)
		{
			if (tickObject == nullptr)
				continue;

			tickObject->Tick(deltaTime);
		}
	}
}
