#pragma once

namespace HopStep
{
	class IComponent
	{
	public :
		virtual void Tick(const float deltaTime) = 0;
	};
}
