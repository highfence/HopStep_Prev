#pragma once
#include <list>
#include "../../HopStep/HopStep/HopStep.h"

class Snake
{
public:

	enum class SnakeDirection : int
	{
		Right, Left, Up, Down
	};

	Snake();
	~Snake();

	void MarchingSnake(SnakeDirection direction);
	void FeedApple();

private :

	SnakeDirection m_Direction = SnakeDirection::Right;
	std::list<HopStep::HSRect*> bodys;
};
