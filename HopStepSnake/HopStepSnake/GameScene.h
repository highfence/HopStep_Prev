#pragma once
#include "Snake.h"
#include "../../HopStep/HopStep/HopStep.h"

class Apple;

class SnakeGameScene final : public HopStep::IScene
{
public:

	virtual bool Init() override;

	virtual void UpdateScene(const float deltaTime) override;

	virtual bool OnChangeScene(HopStep::SceneManager* manager) override;

private :

	Snake::SnakeDirection GetDirectionInput();

	void MakeNewApple();

	bool IsSnakeAteApple();

	Apple* apple = nullptr;
	Snake player;
};

