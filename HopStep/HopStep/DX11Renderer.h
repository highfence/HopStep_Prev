#pragma once
#include "IRenderer.h"

namespace HopStep
{
	inline namespace Internal
	{
		class DX11Renderer final : public IRenderer
		{
		public:

			virtual Result SetRenderQueue(std::shared_ptr<RenderQueue> renderQueue) override;

			virtual Result InitRenderer(HWND windowHanle) override;

			virtual void Render() override;

		private :

		};
	}
}
