#pragma once
#include "HSVector.h"
#include "IRenderCommandProducer.h"

namespace HopStep
{
	class HSRect final : public IRenderCommandProducer
	{
	public:

		HSRect() : m_RectColor(0), m_Center(0) {}
		HSRect& operator=(const HSRect& rhs);

		enum class RectType : int
		{
			LineRect,
			FilledRect
		};

		virtual void Produce(FrameInfo* frameInfo) override;

		HSColor m_RectColor;
		HSVector<float> m_Center;
		HSRect::RectType m_Type = RectType::LineRect;
		float m_Width = 0.0f;
		float m_Height = 0.0f;
	};
}
