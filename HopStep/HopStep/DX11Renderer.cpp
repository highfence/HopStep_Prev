#include "stdafx.h"
#include "Result.h"
#include "DX11Renderer.h"

namespace HopStep
{
	Result DX11Renderer::SetRenderQueue(RenderQueue * renderQueue)
	{
		if (renderQueue == nullptr)
			return Result::InvalidParameter;

		return Result::None;
	}
}
