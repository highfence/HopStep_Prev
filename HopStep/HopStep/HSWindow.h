#pragma once
#include <Windows.h>

namespace HopStep
{
	class HSWindow
	{
	public:

		static void Create(HINSTANCE hInstance, int nCmdShow, std::wstring& name, int width, int height);

	};
}
