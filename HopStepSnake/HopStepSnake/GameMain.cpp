#include <Windows.h>
#include <string>
#include "GameMain.h"
#include "GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HopStep::HSGame SnakeGame;

	HopStep::WindowConfig windowConfig;
	windowConfig.clientWidth = 1200;
	windowConfig.clientHeight = 800;
	windowConfig.instance = hInstance;
	windowConfig.cmdShow = nCmdShow;
	windowConfig.windowName = L"Snake Practice!";
	SnakeGame.SetWindowConfig(windowConfig);
	SnakeGame.InitEngine();

	// Todo : change this sequence easier
	std::shared_ptr<HopStep::IScene> gameScene = std::static_pointer_cast<HopStep::IScene>(std::make_shared<GameScene>());
	SnakeGame.SetStartScene(gameScene);

	SnakeGame.GameStart();

	return 0;
}