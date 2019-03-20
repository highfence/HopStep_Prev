#include "Snake.h"

Snake::Snake()
{
	auto primitiveRect = new HopStep::HSRect();
	primitiveRect->m_RectColor = HopStep::HSColor(1.0f);
	primitiveRect->m_Width = 17;
	primitiveRect->m_Height = 17;
	primitiveRect->m_Type = HopStep::HSRect::RectType::FilledRect;

	int x = 5;
	int y = 5;

	for (int i = 0; i < 4; ++i)
	{
		HopStep::HSRect* body = new HopStep::HSRect(primitiveRect);
		body->m_Center.x = static_cast<float>(x * 20 + 10);
		body->m_Center.y = static_cast<float>(y * 20 + 10);
		bodys.push_back(body);
		body->SetVisible(true);
		--x;
	}

	delete primitiveRect;
}

Snake::~Snake()
{
	bodys.clear();
}

void Snake::MarchingSnake(SnakeDirection inputDirection)
{
	auto headIter = bodys.begin();

	auto inputMarchingVector = GetMarchingVector(inputDirection);
	HopStep::HSVector<float> nextPosition(0);
	nextPosition.x = (*headIter)->m_Center.x + inputMarchingVector.x;
	nextPosition.y = (*headIter)->m_Center.y + inputMarchingVector.y;

	for (auto checkIter = ++(bodys.begin()); checkIter != bodys.end(); ++checkIter)
	{
		if (nextPosition.x == (*checkIter)->m_Center.x && nextPosition.y == (*checkIter)->m_Center.y)
		{
			return;
		}
	}

	m_Direction = inputDirection;

	for (int idx = bodys.size() - 1; idx != 0; --idx)
	{
		bodys[idx]->m_Center = bodys[idx - 1]->m_Center;
	}

	bodys[0]->m_Center = nextPosition;
}

void Snake::FeedApple()
{
	auto endRect = (*bodys.back());
	auto newBody = new HopStep::HSRect(endRect);
	newBody->SetVisible(true);

	bodys.push_back(newBody);
}

bool Snake::IsOverlappedPosition(int x, int y)
{
	for (auto checkIter = ++(bodys.begin()); checkIter != bodys.end(); ++checkIter)
	{
		if (x == (*checkIter)->m_Center.x && y == (*checkIter)->m_Center.y)
		{
			return true;
		}
	}

	return false;
}

HopStep::HSVector<int> Snake::GetHeadPosition() const
{
	HopStep::HSVector<int> pos(0);
	pos.x = static_cast<int>(bodys[0]->m_Center.x);
	pos.y = static_cast<int>(bodys[0]->m_Center.y);
	return pos;
}

HopStep::HSVector<int> Snake::GetMarchingVector(SnakeDirection direction)
{
	HopStep::HSVector<int> marchingVector(0);
	switch (direction)
	{
	case SnakeDirection::Down:
		marchingVector = HopStep::HSVector<int>(0, 20);
		break;
	case SnakeDirection::Up:
		marchingVector = HopStep::HSVector<int>(0, -20);
		break;
	case SnakeDirection::Right:
		marchingVector = HopStep::HSVector<int>(20, 0);
		break;
	case SnakeDirection::Left:
		marchingVector = HopStep::HSVector<int>(-20, 0);
		break;
	}

	return marchingVector;
}

