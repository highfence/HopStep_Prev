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

			static std::shared_ptr<RenderProducerList> Get();

			RenderProducerList() = default;
			~RenderProducerList();

			Result AddProducer(IRenderCommandProducer* producer);
			Result DeleteProducer(IRenderCommandProducer* producer);

			void GatherCommand(std::shared_ptr<FrameInfo> frame);

		private:

			std::vector<IRenderCommandProducer*> m_RenderProducers;
			static std::shared_ptr<RenderProducerList> instance;
		};
	}
}
