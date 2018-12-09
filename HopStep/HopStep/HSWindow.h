#pragma once
#include <Windows.h>
#include "Result.h"

namespace HopStep
{
	struct WindowConfig
	{
		HINSTANCE instance;
		int cmdShow;
		std::wstring windowName;

		int clientWidth;
		int clientHeight;
	};

	class HSWindow
	{
	public:

		HSWindow();
		~HSWindow();

		Result Create(WindowConfig& config);

		HWND WindowHandle;

	private :

		WindowConfig m_Config;
	};
}
