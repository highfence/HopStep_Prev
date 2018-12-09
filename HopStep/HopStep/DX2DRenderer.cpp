#include "stdafx.h"
#include "DX2DRenderer.h"

namespace HopStep
{
	Result DX2DRenderer::SetRenderQueue(std::shared_ptr<RenderQueue> renderQueue)
	{
		if (renderQueue == nullptr)
			return Result::NullParameter;

		m_RenderQueue = renderQueue;

		return Result::None;
	}

	Result DX2DRenderer::InitRenderer(HWND windowHandle)
	{
		m_Hwnd = windowHandle;



		return Result::None;
	}

	void DX2DRenderer::Render()
	{
	}
}
