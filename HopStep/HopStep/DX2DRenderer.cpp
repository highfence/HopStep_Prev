#include "stdafx.h"
#include "RenderQueue.h"
#include "JsonSerialize.h"
#include "HSRect.h"
#include "HSConsoleLogger.h"
#include "RenderCommandProcessor.h"
#include "DX2DRenderer.h"

namespace HopStep
{
	Result DX2DRenderer::SetRenderQueue(Internal::RenderQueue* renderQueue)
	{
		if (renderQueue == nullptr)
			return Result::NullParameter;

		m_RenderQueue = renderQueue;

		return Result::None;
	}

	Result DX2DRenderer::InitRenderer(HWND windowHandle, HSConsoleLogger* logger)
	{
		if (logger = nullptr)
			return Result::NullParameter;

		m_Hwnd = windowHandle;
		m_Logger = logger;

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

		return Result::None;
	}

	void DX2DRenderer::Render()
	{
		if (m_RenderQueue->IsEmpty())
			return;

		ResultChecker renderResult;
		renderResult = CreateDeviceResources();

		m_RenderTarget->BeginDraw();

		m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		auto currentFrame = m_RenderQueue->Peek();

		for (auto& commandList : currentFrame.m_RenderCommands)
		{
			for (RenderCommand command : commandList.second)
			{
				switch (command.type)
				{
				case Internal::RenderCommandType::ClearScreen:
					ClearScreen(Deserialze<ClearScreenCommand>(command).get());
					break;
				case Internal::RenderCommandType::DrawRect:
					DrawRect(Deserialze<DrawRectCommand>(command).get());
					break;
				case Internal::RenderCommandType::DrawSprite:
					DrawSprite(Deserialze<DrawSpriteCommand>(command).get());
					break;
				default:
					m_Logger->Write(LogType::Error, "%s | Unresisted function render type : %d", __FUNCTION__, static_cast<int>(command.type));
					break;
				}
			}
		}

		m_RenderQueue->Pop();

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

		hr = m_Direct2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_Hwnd, size), &m_RenderTarget);

		if (SUCCEEDED(hr) == false)
			return Result::DX2DRenderTargetCreateFailed;

		return Result::None;
	}

	void Internal::DX2DRenderer::ClearScreen(ClearScreenCommand* command)
	{
		if (command == nullptr)
			return;

		HSColor color = command->m_ScreenColor;
		D2D1::ColorF screenColor(color.r, color.g, color.b, color.a);
		m_RenderTarget->Clear(screenColor);
	}

	void Internal::DX2DRenderer::DrawRect(DrawRectCommand* command)
	{
		if (command == nullptr)
			return;

		HSRect rect = command->m_Rect;
		HSColor color = rect.m_RectColor;
		D2D1::ColorF rectColor(color.r, color.g, color.b, color.a);

		D2D1_RECT_F rectangle = D2D1::RectF(
			rect.m_Center.x - rect.m_Width / 2,
			rect.m_Center.y - rect.m_Height / 2,
			rect.m_Center.x + rect.m_Width / 2,
			rect.m_Center.y + rect.m_Height / 2
		);

		ID2D1SolidColorBrush* rectBrush = nullptr;
		HRESULT hr = m_RenderTarget->CreateSolidColorBrush(rectColor, &rectBrush);
		if (SUCCEEDED(hr) == false)
		{
			m_Logger->Write(LogType::Error, "%s | Brush creation failed", __FUNCTION__);
			return;
		}

		if (rect.m_Type == HSRect::RectType::FilledRect)
		{
			m_RenderTarget->FillRectangle(&rectangle, rectBrush);
		}
		else if (rect.m_Type == HSRect::RectType::LineRect)
		{
			m_RenderTarget->DrawRectangle(&rectangle, rectBrush);
		}

		SafeRelease(&rectBrush);
	}

	void Internal::DX2DRenderer::DrawSprite(DrawSpriteCommand* command)
	{
		if (command == nullptr)
			return;

		// 커맨드안에는 이미지의 핸들을 받도록 하자.
		// 스프라이트렌더러는 핸들을 관리해야한다.
	}
}
