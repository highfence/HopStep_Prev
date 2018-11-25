#pragma once
#include <stack>
#include "HSWindow.h"
#include "IScene.h"
#include "Result.h"
#include "Timer.h"

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
		Result OpenWindow();

		void UpdateEngine();
		WindowConfig m_WindowConfig;

		std::stack<IScene*> m_Scene;
		std::unique_ptr<HSWindow> m_GameWindow;
		std::unique_ptr<GameTimer> m_Timer;

		float m_AccTime = 0.0f;
	};
}
