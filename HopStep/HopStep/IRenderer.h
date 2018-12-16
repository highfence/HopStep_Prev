#pragma once
#include "HSConsoleLogger.h"
#include "RenderQueue.h"

namespace HopStep
{
	inline namespace Internal
	{
		__interface IRenderer
		{
			virtual Result SetRenderQueue(RenderQueue* renderQueue) = 0;

			virtual Result InitRenderer(HWND windowHandle, HSConsoleLogger* logger) = 0;

			virtual Result ReleaseRenderer() = 0;

			virtual void Render() = 0;
		};
	}
}
