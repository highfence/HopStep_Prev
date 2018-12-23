#pragma once
#include "../../HopStep/HopStep/HopStep.h"

class Apple
{
public:

	Apple(int, int);
	~Apple();

	HopStep::HSVector<int> position;

	HopStep::HSRect rect;
};

