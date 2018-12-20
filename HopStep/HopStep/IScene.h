#pragma once

namespace HopStep
{
	class SceneManager;

	__interface IScene
	{
		virtual void UpdateScene(const float deltaTime) = 0;

		virtual bool Init() = 0;

		virtual bool OnChangeScene(SceneManager* manager) = 0;
	};
}
