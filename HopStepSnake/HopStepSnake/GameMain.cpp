#include <Windows.h>
#include <string>
#include "GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	std::wstring gameWindowName = L"Snake Practice!";
	HopStep::HSWindow::Create(hInstance, nCmdShow, gameWindowName, 1200, 800);

	return 0;
}