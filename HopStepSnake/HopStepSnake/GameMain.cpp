#include <Windows.h>
#include <string>
#include "GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HopStep::WindowConfig windowConfig;
	windowConfig.clientWidth = 1200;
	windowConfig.clientHeight = 800;
	windowConfig.instance = hInstance;
	windowConfig.cmdShow = nCmdShow;
	windowConfig.windowName = L"Snake Practice!";




	return 0;
}