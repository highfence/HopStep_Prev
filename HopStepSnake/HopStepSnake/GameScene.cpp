#include "GameScene.h"

constexpr int widthCellCount = 24;
constexpr int heightCellCount = 16;
constexpr int cellPixel = 20;

bool SnakeGameScene::Init()
{
	return true;
}

void SnakeGameScene::UpdateScene(float deltaTime)
{

}

bool SnakeGameScene::OnChangeScene(HopStep::SceneManager * manager)
{
	return false;
}
