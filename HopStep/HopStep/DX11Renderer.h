#pragma once
#include "IRenderer.h"

namespace HopStep
{
	inline namespace Internal
	{
		class RenderQueue;

		class DX11Renderer final : public IRenderer
		{
		public:

			virtual Result SetRenderQueue(RenderQueue* renderQueue) override;

			virtual Result InitRenderer(HWND windowHandle) override;

			virtual Result ReleaseRenderer() override;

			virtual void Render() override;

		private :

		};
	}
}
