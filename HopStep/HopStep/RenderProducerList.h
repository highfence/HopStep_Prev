#pragma once
#include "FrameInfo.h"

namespace HopStep
{
	inline namespace Internal
	{
		class IRenderCommandProducer;

		class RenderProducerList
		{
		public:

			RenderProducerList();
			~RenderProducerList();

			Result AddProducer(IRenderCommandProducer* producer);
			Result DeleteProducer(IRenderCommandProducer* producer);

			void GatherCommand(std::shared_ptr<FrameInfo> frame);

		private:

			std::vector<IRenderCommandProducer*> m_RenderProducers;

		};
		static RenderProducerList* thisGameRendererList = nullptr;
	}
}
