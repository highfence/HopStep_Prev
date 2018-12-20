#include <Windows.h>
#include <string>
#include "GameMain.h"
#include "GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	using namespace HopStep;

	HSGame SnakeGame;

	WindowConfig windowConfig;
	windowConfig.clientWidth = 480;
	windowConfig.clientHeight = 320;
	windowConfig.instance = hInstance;
	windowConfig.cmdShow = nCmdShow;
	windowConfig.windowName = L"Snake Practice!";
	windowConfig.backgroundColor = HopStep::HSColor(0.f, 0.f, 0.f, 1.0f);

	SnakeGame.InitEngine(windowConfig);

	// Todo : change this sequence easier
	std::shared_ptr<IScene> gameScene = std::static_pointer_cast<IScene>(std::make_shared<SnakeGameScene>());
	SnakeGame.SetStartScene(gameScene);

	SnakeGame.GameStart();

	return 0;
}