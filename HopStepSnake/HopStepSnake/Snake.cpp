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
		body->m_Center.x = x * 20 + 10;
		body->m_Center.y = y * 20 + 10;
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

void Snake::MarchingSnake(SnakeDirection direction)
{
}

void Snake::FeedApple()
{

}
