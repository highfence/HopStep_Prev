#include "stdafx.h"
#include "HSGame.h"

namespace HopStep
{
	HSGame::HSGame()
	{
	}

	HSGame::~HSGame()
	{
	}

	void HSGame::GameStart()
	{
		MSG message;
		while (true)
		{
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
					break;
			}
			else
			{
				// whole game update
			}
		}
	}

	void HSGame::SetWindowConfig(WindowConfig& config)
	{
	}

	void HSGame::SetStartScene(IScene* startScene)
	{
		if (startScene == nullptr)
			return;

		m_Scene.push(startScene);
	}

	Result HSGame::InitEngine()
	{
		m_Scene.empty();
		m_GameWindow = std::make_unique<HSWindow>();

		return Result::None;
	}
}
