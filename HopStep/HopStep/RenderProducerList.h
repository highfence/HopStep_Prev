#pragma once
#include <atomic>

namespace HopStep
{
	inline namespace Internal
	{
		class IRenderCommandProducer;
		class FrameInfo;

		class RenderProducerList
		{
		public:

			static std::shared_ptr<RenderProducerList> Get();

			RenderProducerList() = default;
			~RenderProducerList();

			Result AddProducer(IRenderCommandProducer* producer);
			Result DeleteProducer(IRenderCommandProducer* producer);

			void GatherCommand(FrameInfo* frame);

		private:

			std::vector<IRenderCommandProducer*> m_RenderProducers;
			static std::shared_ptr<RenderProducerList> instance;
		};
	}
}
