#pragma once

namespace HopStep
{
	class SceneManager;

	class IScene
	{
	public :

		virtual void UpdateScene(const float deltaTime) = 0;

		virtual bool Init() = 0;

		virtual bool OnChangeScene(SceneManager* manager) = 0;
	};
}
