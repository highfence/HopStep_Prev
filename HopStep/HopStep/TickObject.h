#pragma once
#include "TickObjectList.h"

namespace HopStep
{
	inline namespace Internal
	{
		class TickObject
		{
		public :

			TickObject()
			{
				auto objectList = TickObjectList::Get();
				if (objectList == nullptr)
				{
					HSDebug::CheckResult(Result::GetSingletonFailed);
					return;
				}
				
				objectList->AddObject(this);
			}

			virtual ~TickObject()
			{
				auto objectList = TickObjectList::Get();
				if (objectList == nullptr)
				{
					HSDebug::CheckResult(Result::GetSingletonFailed);
					return;
				}

				objectList->DeleteObject(this);;
			}

			virtual void Tick(const float deltaTime) {};
		};
	}
}
