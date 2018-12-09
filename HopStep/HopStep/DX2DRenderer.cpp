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

		HRESULT hr;
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Direct2DFactory);
		if (hr != S_OK)
			return Result::DirectX2DRenderFactoryInitializeFailed;

		return Result::None;
	}

	void DX2DRenderer::Render()
	{
	}
}
