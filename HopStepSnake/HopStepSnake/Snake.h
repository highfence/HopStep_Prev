#pragma once
#include <vector>
#include "../../HopStep/HopStep/HopStep.h"

class Snake
{
public:

	enum class SnakeDirection : int
	{
		None, Right, Left, Up, Down
	};

	Snake();
	~Snake();

	void MarchingSnake(SnakeDirection direction);
	void FeedApple();
	SnakeDirection GetDirection() const { return m_Direction; }
	HopStep::HSVector<int> GetHeadPosition() const;

private :

	HopStep::HSVector<int> GetMarchingVector(SnakeDirection direction);

	SnakeDirection m_Direction = SnakeDirection::Right;
	std::vector<HopStep::HSRect*> bodys;
};
