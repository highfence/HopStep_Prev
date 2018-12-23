#include "Apple.h"


Apple::Apple(int x, int y)
	: position(0), rect(0)
{
	position = HopStep::HSVector<int>(x, y);
	rect.m_Center.x = x;
	rect.m_Center.y = y;
	rect.m_Type = HopStep::HSRect::RectType::FilledRect;
	rect.m_Width = 17;
	rect.m_Height = 17;
	rect.m_RectColor = HopStep::HSColor(1.0f, 0.0f, 0.0f);
	rect.SetVisible(true);
}

Apple::~Apple()
{
	rect.SetVisible(false);
}
