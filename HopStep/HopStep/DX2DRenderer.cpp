#include "stdafx.h"
#include "RenderQueue.h"
#include "JsonSerialize.h"
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

		m_Processor = std::make_unique<RenderCommandProcessor>();

		ResultChecker initResult;
		initResult = RegistRenderFunctions();

		return initResult.result;
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
		if (m_RenderQueue->IsEmpty())
			return;

		ResultChecker renderResult;
		renderResult = CreateDeviceResources();

		m_RenderTarget->BeginDraw();

		m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		auto currentFrame = m_RenderQueue->Peek();

		m_Processor->Process(currentFrame);

		m_RenderQueue->Pop();

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

	Result Internal::DX2DRenderer::RegistRenderFunctions()
	{
		if (m_Processor == nullptr)
			return Result::NotInitializeYet;

		m_Processor->RegistRenderFunction(RenderCommandType::ClearScreen, std::bind(&DX2DRenderer::ClearScreen, this, std::placeholders::_1));
		m_Processor->RegistRenderFunction(RenderCommandType::DrawRect   , std::bind(&DX2DRenderer::DrawRect	  , this, std::placeholders::_1));

		return Result::None;
	}

	void Internal::DX2DRenderer::ClearScreen(std::shared_ptr<RenderCommand> renderCommand)
	{
		ClearScreenCommand command;
		const int bodySize = renderCommand->bodySize;
		std::string rawJson;
		rawJson.assign(renderCommand->body, renderCommand->bodySize);

		Json::Value root;
		Json::CharReaderBuilder builder;
		Json::CharReader* reader = builder.newCharReader();;

		if (reader)
		{
			reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.size(), &root, nullptr);
			command.Deserialize(root);

			delete reader;

			HSColor color = command.m_ScreenColor;
			D2D1::ColorF screenColor(color.r, color.g, color.b, color.a);
			m_RenderTarget->Clear(screenColor);
		}

		delete[] renderCommand->body;
	}

	void Internal::DX2DRenderer::DrawRect(std::shared_ptr<RenderCommand> renderCommand)
	{
		if (m_RenderTarget == nullptr)
			return;

		DrawRectCommand command;
		const int bodySize = renderCommand->bodySize;
		std::string rawJson;
		rawJson.assign(renderCommand->body, renderCommand->bodySize);;

		Json::Value root;
		Json::CharReaderBuilder builder;
		Json::CharReader* reader = builder.newCharReader();;

		if (reader == nullptr)
			return;

		reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.size(), &root, nullptr);
		command.Deserialize(root);

		delete reader;

		HSColor color = command.m_RectColor;
		D2D1::ColorF rectColor(color.r, color.g, color.b, color.a);

		D2D1_RECT_F rectangle = D2D1::RectF(
			command.m_Center.x - command.m_Width / 2,
			command.m_Center.y - command.m_Height / 2,
			command.m_Center.x + command.m_Width / 2,
			command.m_Center.y + command.m_Height / 2
		);

		ID2D1SolidColorBrush* rectBrush = nullptr;
		HRESULT hr = m_RenderTarget->CreateSolidColorBrush(rectColor, &rectBrush);
		if (SUCCEEDED(hr) == false)
		{
			m_Logger->Write(LogType::Error, "%s | Brush creation failed", __FUNCTION__);
			delete[] renderCommand->body;
			return;
		}

		if (command.m_Type == DrawRectCommand::RectType::FilledRect)
		{
			m_RenderTarget->FillRectangle(&rectangle, rectBrush);
		}
		else if (command.m_Type == DrawRectCommand::RectType::LineRect)
		{
			m_RenderTarget->DrawRectangle(&rectangle, rectBrush);
		}

		delete[] renderCommand->body;
		SafeRelease(&rectBrush);
	}
}
