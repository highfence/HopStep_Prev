#pragma once
#include "IComponent.h"

namespace HopStep
{
	class SpriteRenderer :
		public IComponent
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Tick(const float deltaTime) override;
	};
}
