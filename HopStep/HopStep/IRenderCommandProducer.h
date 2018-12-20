#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		class FrameInfo;

		class IRenderCommandProducer
		{
		public :

			IRenderCommandProducer() {}

			virtual ~IRenderCommandProducer()
			{
				UnregistMe();
			}

			virtual void SetVisible(bool visivility);
			virtual void Produce(FrameInfo* frameInfo) = 0;

		protected :

			virtual void RegistMe();
			virtual void UnregistMe();
		};
	}
}