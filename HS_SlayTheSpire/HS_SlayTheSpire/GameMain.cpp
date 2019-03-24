#include <Windows.h>
#include <string>
#include "GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	using namespace HopStep;

	HSGame HS_SlayTheSpire;
	WindowConfig config = WindowConfig();
	config.instance = hInstance;
	config.cmdShow = nCmdShow;
	config.clientHeight = 1200;
	config.clientWidth = 800;
	config.windowName = L"Trying Slay the Spire...";
	HS_SlayTheSpire.InitEngine(config);

	TitleScene* titleScene = new TitleScene();
	HS_SlayTheSpire.SetStartScene(titleScene);

	HS_SlayTheSpire.GameStart();

	return 0;
}
