#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		class IRenderCommandProducer
		{
		public :

			IRenderCommandProducer() {}

			virtual ~IRenderCommandProducer()
			{
				UnregistMe();
			}

			virtual void SetVisible(bool visivility);
			virtual void Produce(std::shared_ptr<FrameInfo> frameInfo) = 0;

		protected :

			virtual void RegistMe();
			virtual void UnregistMe();
		};
	}
}