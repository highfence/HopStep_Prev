#pragma once
#include "IRenderer.h"

namespace HopStep
{
	inline namespace Internal
	{
		class DX11Renderer final : public IRenderer
		{
		public:

			virtual Result SetRenderQueue(RenderQueue* renderQueue) override;

			virtual Result InitRenderer() override;

			virtual void Render() override;

		private :

			RenderQueue* m_RenderQueue;

		};
	}
}
