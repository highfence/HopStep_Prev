#include "stdafx.h"
#include "DX2DRenderer.h"

namespace HopStep
{
	Result DX2DRenderer::SetRenderQueue(RenderQueue* renderQueue)
	{
		if (renderQueue == nullptr)
			return Result::NullParameter;

		m_RenderQueue = renderQueue;

		return Result::None;
	}

	Result DX2DRenderer::InitRenderer(HWND windowHandle)
	{
		m_Hwnd = windowHandle;

		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Direct2DFactory);
		if (hr != S_OK)
			return Result::DX2DRenderFactoryInitializeFailed;

		return Result::None;
	}

	Result Internal::DX2DRenderer::ReleaseRenderer()
	{
		SafeRelease(&m_Direct2DFactory);
		SafeRelease(&m_RenderTarget);
		SafeRelease(&m_BackGroundColorBrush);
		SafeRelease(&m_pLightSlateGrayBrush);
		SafeRelease(&m_pCornflowerBlueBrush);

		return Result::None;
	}

	void DX2DRenderer::Render()
	{
		ResultChecker renderResult;
		renderResult = CreateDeviceResources();

		m_RenderTarget->BeginDraw();

		m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

#pragma region DEBUG

		//// Draw a grid background.
		//D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

		//int width = static_cast<int>(rtSize.width);
		//int height = static_cast<int>(rtSize.height);

		//for (int x = 0; x < width; x += 10)
		//{
		//	m_pRenderTarget->DrawLine(
		//		D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
		//		D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
		//		m_pLightSlateGrayBrush,
		//		0.5f
		//	);
		//}

		//for (int y = 0; y < height; y += 10)
		//{
		//	m_pRenderTarget->DrawLine(
		//		D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
		//		D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
		//		m_pLightSlateGrayBrush,
		//		0.5f
		//	);
		//}

		//// Draw two rectangles.
		//D2D1_RECT_F rectangle1 = D2D1::RectF(
		//	rtSize.width / 2 - 50.0f,
		//	rtSize.height / 2 - 50.0f,
		//	rtSize.width / 2 + 50.0f,
		//	rtSize.height / 2 + 50.0f
		//);

		//D2D1_RECT_F rectangle2 = D2D1::RectF(
		//	rtSize.width / 2 - 100.0f,
		//	rtSize.height / 2 - 100.0f,
		//	rtSize.width / 2 + 100.0f,
		//	rtSize.height / 2 + 100.0f
		//);

		//// Draw a filled rectangle.
		//m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);

		//// Draw the outline of a rectangle.
		//m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);

#pragma endregion

		m_RenderTarget->EndDraw();
	}

	Result Internal::DX2DRenderer::CreateDeviceResources()
	{
		if (m_RenderTarget != nullptr)
			return Result::None;

		HRESULT hr;
		RECT rc;
		GetClientRect(m_Hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// Create a Direct2D render target.
		hr = m_Direct2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_Hwnd, size), &m_RenderTarget);
		if (SUCCEEDED(hr) == false)
			return Result::DX2DRenderTargetCreateFailed;

		// Create a gray brush.
		hr = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_pLightSlateGrayBrush);
		if (SUCCEEDED(hr) == false)
			return Result::DX2DRenderTargetCreateFailed;

		// Create a blue brush.
		hr = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &m_pCornflowerBlueBrush);
		if (SUCCEEDED(hr) == false)
			return Result::DX2DRenderTargetCreateFailed;

		return Result::None;
	}
}
