#include "stdafx.h"
#include "HopStep.h"
#include "DX11Renderer.h"

namespace HopStep
{
	Result DX11Renderer::SetRenderQueue(RenderQueue * renderQueue)
	{
		if (renderQueue == nullptr)
			return Result::NullParameter;

		m_RenderQueue = renderQueue;

		return Result::None;
	}
}
