#pragma once

namespace HopStep
{
	__interface IScene
	{
		virtual void UpdateScene(const float deltaTime) = 0;

		virtual bool Init() = 0;
	};
}
