#pragma once
#include <Windows.h>

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

		void Create(WindowConfig config);

	private :

		WindowConfig m_Config;

	};
}
