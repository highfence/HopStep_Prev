#include "stdafx.h"
#include "HopStep.h"
#include "Timer.h"
#include "HSGame.h"

namespace HopStep
{
	HSGame::HSGame()
	{
		InitEngine();
	}

	HSGame::~HSGame()
	{
	}

	void HSGame::GameStart()
	{
		OpenWindow();

		MSG message;
		while (true)
		{
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
					break;

				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				// whole game update
				UpdateEngine();
			}
		}
	}

	void HSGame::SetWindowConfig(WindowConfig& config)
	{
		m_WindowConfig = config;
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

		m_Timer = std::make_unique<GameTimer>();
		m_Timer->InitTimer();

		m_GameWindow = std::make_unique<HSWindow>();

		return Result::None;
	}

	Result HSGame::OpenWindow()
	{
		Result funcResult = Result::None;

		funcResult = m_GameWindow->Create(m_WindowConfig);
		HSDebug::CheckResult(funcResult);

		return Result::None;
	}

	constexpr float frameTime = 1.0f / 60.0f;
	void HSGame::UpdateEngine()
	{
		m_Timer->ProcessTime();
		static float deltaTime = m_Timer->GetElapsedTime();

		m_AccTime += deltaTime;
		if (m_AccTime > frameTime)
		{
			m_AccTime = 0.0f;
		}
	}
}
