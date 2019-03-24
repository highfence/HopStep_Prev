#include "stdafx.h"
#include "HSConsoleLogger.h"
#include "HsWindow.h"

namespace HopStep
{
	std::wstring windowClassName = TEXT("HSBasicWindow");

	LRESULT CALLBACK HSBasicWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	HSWindow::HSWindow(HSConsoleLogger* logger)
		: m_Logger(logger), WindowHandle(NULL)
	{
	}

	HSWindow::~HSWindow()
	{
	}

	Result HSWindow::Create(WindowConfig& config)
	{
		m_Config = config;

		WNDCLASSEX wc;

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = HSBasicWindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_Config.instance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = windowClassName.c_str();
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
			return Result::WindowClassRegistFailed;

		WindowHandle = CreateWindowEx(WS_EX_CLIENTEDGE,	windowClassName.c_str(), m_Config.windowName.c_str(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			m_Config.clientWidth, m_Config.clientHeight, NULL, NULL, m_Config.instance, NULL);

		if (WindowHandle == NULL)
			return Result::WindowInvalidHandleReturn;

		ShowWindow(WindowHandle, m_Config.cmdShow);
		UpdateWindow(WindowHandle);

		this->SetVisible(true);

		return Result::None;
	}

	void HSWindow::Produce(FrameInfo& frameInfo)
	{
		ClearScreenCommand command;
		command.m_ScreenColor = m_Config.backgroundColor;
		command.m_IsColorChanged = true;

		std::string jsonString;
		JsonSerializer::Serialize(&command, jsonString);

		auto renderCommand = std::make_shared<RenderCommand>();

		char* body = new char[jsonString.size() + 1];
		std::copy(jsonString.begin(), jsonString.end(), body);
		body[jsonString.size()] = '\0';

		renderCommand->body = body;
		renderCommand->bodySize = jsonString.size();

		renderCommand->type = RenderCommandType::ClearScreen;

		frameInfo.AddRenderCommand(*renderCommand.get());
	}
}