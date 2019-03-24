#pragma once
#include "Snake.h"
#include "../../HopStep/HopStep/HopStep.h"

class Apple;
using IScene = HopStep::IScene;
using SceneManager = HopStep::SceneManager;

class SnakeGameScene final : public IScene
{
public:

	virtual bool Init() override;

	virtual void UpdateScene(const float deltaTime) override;

	virtual bool OnChangeScene(SceneManager* manager) override;

private :

	Snake::SnakeDirection GetDirectionInput();

	void MakeNewApple();
	void DeleteApple();

	bool IsSnakeAteApple();

	Apple* apple = nullptr;
	Snake snake;
};

