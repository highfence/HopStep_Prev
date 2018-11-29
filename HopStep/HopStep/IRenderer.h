#pragma once
#include "Pool.h"
#include "SwapContainer.h"
#include "HopStep.h"
#include "RenderCommand.h"

namespace HopStep
{
	inline namespace Internal
	{
		using RenderQueue = SwapContainer<Pool<RenderCommand>>;

		struct IRenderer
		{
			virtual Result SetRenderQueue(RenderQueue* renderQueue) = 0;

			virtual Result InitRenderer() = 0;

			virtual void Render() = 0;
		};

		class RendererFactory
		{
		public :
			static IRenderer* GetRenderer();
		};
	}
}
