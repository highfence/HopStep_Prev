#include <Windows.h>
#include <string>
#include "GameMain.h"
#include "GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HopStep::WindowConfig windowConfig;
	windowConfig.clientWidth = 1200;
	windowConfig.clientHeight = 800;
	windowConfig.instance = hInstance;
	windowConfig.cmdShow = nCmdShow;
	windowConfig.windowName = L"Snake Practice!";

	HopStep::HSGame SnakeGame;
	SnakeGame.SetWindowConfig(windowConfig);

	std::shared_ptr<HopStep::IScene> gameScene = std::make_shared<GameScene>();
	SnakeGame.SetStartScene(gameScene);

	SnakeGame.GameStart();

	return 0;
}