#include "GameScene.h"

constexpr int widthCellCount = 24;
constexpr int heightCellCount = 16;
constexpr int cellPixel = 20;

bool SnakeGameScene::Init()
{
	return true;
}

constexpr float tickTime = 10.0f;
void SnakeGameScene::UpdateScene(float deltaTime)
{
	static float m_AccTime = 0.0f;
	m_AccTime += deltaTime;

	static Snake::SnakeDirection direction = Snake::SnakeDirection::Right;
	auto currentDirection = GetDirectionInput(player.GetDirection());
	if (currentDirection != Snake::SnakeDirection::None)
	{
		direction = currentDirection;
	}
	
	if (m_AccTime > tickTime)
	{
		player.MarchingSnake(direction);


		m_AccTime = 0.0f;
	}
}

bool SnakeGameScene::OnChangeScene(HopStep::SceneManager * manager)
{
	return false;
}

Snake::SnakeDirection SnakeGameScene::GetDirectionInput(Snake::SnakeDirection basicInput)
{
	auto inputLayer = HopStep::InputLayer::Get();
	if (inputLayer == nullptr)
		return Snake::SnakeDirection::None;

	if (inputLayer->GetKeyState(VK_LEFT) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_LEFT) == HopStep::KeyState::PushKey)
	{
		return Snake::SnakeDirection::Left;
	}
	else if (inputLayer->GetKeyState(VK_RIGHT) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_RIGHT) == HopStep::KeyState::PushKey)
	{
		return Snake::SnakeDirection::Right;
	}
	else if (inputLayer->GetKeyState(VK_UP) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_UP) == HopStep::KeyState::PushKey)
	{
		return Snake::SnakeDirection::Up;
	}
	else if (inputLayer->GetKeyState(VK_DOWN) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_DOWN) == HopStep::KeyState::PushKey)
	{
		return Snake::SnakeDirection::Down;
	}

	return Snake::SnakeDirection::None;
}
