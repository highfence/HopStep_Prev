#pragma once
#include "Pool.h"
#include "HopStep.h"
#include "RenderCommand.h"

namespace HopStep
{
	inline namespace Internal
	{
		using RenderQueue = Pool<RenderCommand>;

		__interface IRenderer
		{
			virtual Result SetRenderQueue(RenderQueue* renderQueue) = 0;
		};

		FactoryClass RendererFactory
		{
			static IRenderer* GetRenderer();
		};
	}
}
