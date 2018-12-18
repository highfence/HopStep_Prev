#pragma once

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

			void GatherCommand(RenderQueue* queue);

		private:

			std::vector<IRenderCommandProducer*> m_RenderProducers;

		};
		static RenderProducerList* thisGameRendererList = nullptr;
	}
}
