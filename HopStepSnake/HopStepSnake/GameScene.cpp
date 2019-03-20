#include <random>
#include "Apple.h"
#include "GameScene.h"

constexpr int widthCellCount = 24;
constexpr int heightCellCount = 16;
constexpr int cellPixel = 20;

constexpr float tickTime = 30.0f;

bool SnakeGameScene::Init()
{
	MakeNewApple();
	return true;
}

void SnakeGameScene::UpdateScene(float deltaTime)
{
	static float m_AccTime = 0.0f;
	m_AccTime += deltaTime;

	auto direction = GetDirectionInput();
	
	if (m_AccTime > tickTime)
	{
		if (IsSnakeAteApple())
		{
			DeleteApple();
			snake.FeedApple();
			MakeNewApple();
		}

		snake.MarchingSnake(direction);
		m_AccTime = 0.0f;
	}
}

bool SnakeGameScene::OnChangeScene(HopStep::SceneManager * manager)
{
	if (manager == nullptr)
		return false;

	return false;
}

Snake::SnakeDirection SnakeGameScene::GetDirectionInput()
{
	static Snake::SnakeDirection direction = Snake::SnakeDirection::Right;

	auto newDirection = Snake::SnakeDirection::None;

	auto inputLayer = HopStep::InputLayer::Get();
	if (inputLayer == nullptr)
		newDirection = Snake::SnakeDirection::None;

	if (inputLayer->GetKeyState(VK_LEFT) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_LEFT) == HopStep::KeyState::PushKey)
	{
		newDirection = Snake::SnakeDirection::Left;
	}
	else if (inputLayer->GetKeyState(VK_RIGHT) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_RIGHT) == HopStep::KeyState::PushKey)
	{
		newDirection = Snake::SnakeDirection::Right;
	}
	else if (inputLayer->GetKeyState(VK_UP) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_UP) == HopStep::KeyState::PushKey)
	{
		newDirection = Snake::SnakeDirection::Up;
	}
	else if (inputLayer->GetKeyState(VK_DOWN) == HopStep::KeyState::HoldKey
		|| inputLayer->GetKeyState(VK_DOWN) == HopStep::KeyState::PushKey)
	{
		newDirection =Snake::SnakeDirection::Down;
	}

	if (newDirection != Snake::SnakeDirection::None)
		direction = newDirection;

	return direction;
}

void SnakeGameScene::MakeNewApple()
{
	if (apple != nullptr)
		return;

	int x, y;
	do
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> xdist(1, 23);
		std::uniform_int_distribution<int> ydist(1, 15);

		x = xdist(mt) * 20 + 10;
		y = ydist(mt) * 20 + 10;

	} while (snake.IsOverlappedPosition(x, y));
	
	apple = new Apple(x, y);
}

void SnakeGameScene::DeleteApple()
{
	if (apple != nullptr)
	{
		delete apple;
		apple = nullptr;
	}
}

bool SnakeGameScene::IsSnakeAteApple()
{
	if (apple == nullptr)
		return true;

	auto headPosition = snake.GetHeadPosition();
	if (headPosition.x == apple->position.x && headPosition.y == apple->position.y)
		return true;

	return false;
}
