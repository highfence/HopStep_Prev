#pragma once
#include "TickObjectList.h"

namespace HopStep
{
	inline namespace Internal
	{
		class ITickObject
		{
		public :

			ITickObject()
			{
				auto objectList = TickObjectList::Get();
				if (objectList == nullptr)
				{
					HSDebug::CheckResult(Result::GetSingletonFailed);
					return;
				}
				
				objectList->AddObject(this);
			}

			virtual ~ITickObject()
			{
				auto objectList = TickObjectList::Get();
				if (objectList == nullptr)
				{
					HSDebug::CheckResult(Result::GetSingletonFailed);
					return;
				}

				objectList->DeleteObject(this);;
			}

			virtual void Tick(const float deltaTime) = 0;
		};
	}
}
