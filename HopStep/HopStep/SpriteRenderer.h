#pragma once
#
#include "IRenderCommandProducer.h"
#include "IComponent.h"

namespace HopStep
{
	class SpriteRenderer :
		public IComponent,
		public IRenderCommandProducer
	{
	public:

		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Tick(const float deltaTime) override;
		virtual void Produce(FrameInfo& frameInfo) override;

		bool InitWithFileName(const std::string& fileName);

	protected :

		HSHandle m_SpriteHandle;
	};
}
