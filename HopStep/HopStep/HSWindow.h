#pragma once
#include <Windows.h>
#include "HSColor.h"
#include "Result.h"
#include "IRenderCommandProducer.h"

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

	class HSWindow final : IRenderCommandProducer
	{
	public:

		HSWindow(HSConsoleLogger* logger);
		~HSWindow();

		Result Create(WindowConfig& config);

		HWND WindowHandle;

		virtual void Produce(std::shared_ptr<FrameInfo> frameInfo) override;

	private :

		WindowConfig m_Config;
		HSConsoleLogger* m_Logger;
	};
}
