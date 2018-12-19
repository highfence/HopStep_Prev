#pragma once
#include "HSDebug.h"
#include "RenderProducerList.h"

namespace HopStep
{
	inline namespace Internal
	{
		class IRenderCommandProducer
		{
		public :

			IRenderCommandProducer()
			{
				auto producerList = RenderProducerList::Get();
				if (producerList == nullptr)
				{
					HSDebug::CheckResult(Result::GetSingletonFailed);
					return;
				}
				producerList->AddProducer(this);
			}

			virtual ~IRenderCommandProducer()
			{
				auto producerList = RenderProducerList::Get();
				if (producerList == nullptr)
				{
					HSDebug::CheckResult(Result::GetSingletonFailed);
					return;
				}
				producerList->DeleteProducer(this);
			}

			virtual void Produce(std::shared_ptr<FrameInfo> frameInfo) = 0;
		};
	}
}