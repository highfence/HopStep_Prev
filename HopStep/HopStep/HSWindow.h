#pragma once
#include <Windows.h>
#include "HSColor.h"
#include "Result.h"

namespace HopStep
{
	class HSConsoleLogger;

	struct WindowConfig
	{
		HINSTANCE instance;
		int cmdShow;
		std::wstring windowName;

		int clientWidth;
		int clientHeight;

		HSColor backgroundColor;
	};

	class HSWindow
	{
	public:

		HSWindow(HSConsoleLogger* logger);
		~HSWindow();

		Result Create(WindowConfig& config);

		HWND WindowHandle;

	private :

		WindowConfig m_Config;
		HSConsoleLogger* m_Logger;
	};
}
