#pragma once

#include "Pool.h"
#include "SwapContainer.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

namespace HopStep
{
	inline namespace Internal
	{
		__interface IRenderer
		{
			virtual Result SetRenderQueue(RenderQueue* renderQueue) = 0;

			virtual Result InitRenderer(HWND windowHandle) = 0;

			virtual Result ReleaseRenderer() = 0;

			virtual void Render() = 0;
		};
	}
}
