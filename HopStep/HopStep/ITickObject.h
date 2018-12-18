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
				if (thisGameTickObjects == nullptr)
					return;
				
				thisGameTickObjects->AddObject(this);
			}

			virtual ~ITickObject()
			{
				if (thisGameTickObjects == nullptr)
					return;

				thisGameTickObjects->DeleteObject(this);
			}

			virtual void Tick(const float deltaTime) = 0;
		};
	}
}
