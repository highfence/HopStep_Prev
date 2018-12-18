#pragma once
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
				if (thisGameRendererList == nullptr)
					return;

				thisGameRendererList->AddProducer(this);
			}

			virtual ~IRenderCommandProducer()
			{
				if (thisGameRendererList == nullptr)
					return;

				thisGameRendererList->DeleteProducer(this);
			}

			virtual void Produce(std::shared_ptr<FrameInfo> frameInfo) = 0;
		};
	}
}