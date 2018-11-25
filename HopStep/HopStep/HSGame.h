#pragma once
#include <stack>
#include "HSWindow.h"
#include "IScene.h"
#include "Result.h"

namespace HopStep
{
	class HSGame
	{
	public:

		HSGame();
		~HSGame();

		void GameStart();

		void SetWindowConfig(WindowConfig& config);

		void SetStartScene(IScene* startScene);

	private :

		Result InitEngine();

		WindowConfig m_WindowConfig;

		std::stack<IScene*> m_Scene;
		std::unique_ptr<HSWindow> m_GameWindow;

	};
}
