#pragma once

#include "Pool.h"
#include "SwapContainer.h"
#include "RenderCommand.h"

namespace HopStep
{
	inline namespace Internal
	{
		using RenderQueue = SwapContainer<Pool<RenderCommand>>;

		__interface IRenderer
		{
			virtual Result SetRenderQueue(std::shared_ptr<RenderQueue> renderQueue) = 0;

			virtual Result InitRenderer() = 0;

			virtual void Render() = 0;
		};
	}
}
