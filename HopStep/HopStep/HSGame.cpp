#include "stdafx.h"
#include "HopStep.h"
#include "Timer.h"
#include "DX2DRenderer.h"
#include "HSGame.h"

namespace HopStep
{
	HSGame::HSGame()
	{
		InitEngine();
	}

	HSGame::~HSGame()
	{
		Release();
	}

	void HSGame::Release()
	{
		
	}

	constexpr float frameTime = 1.0f / 60.0f;
	void HSGame::GameStart()
	{
		OpenWindow();

		MSG message;
		while (true)
		{
			m_Timer->ProcessTime();
			static float deltaTime = m_Timer->GetElapsedTime();

			m_AccTime += deltaTime;
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

		auto pool1 = new Pool<RenderCommand>();
		auto pool2 = new Pool<RenderCommand>();
		pool1->Init(1024);
		pool2->Init(1024);

		m_RenderQueue = std::make_shared<RenderQueue>(pool1, pool2);

		m_GameWindow = std::make_unique<HSWindow>();

		m_InputLayer = std::make_shared<InputLayer>();

		return Result::None;
	}

	Result HSGame::OpenWindow()
	{
		Result funcResult = Result::None;

		funcResult = m_GameWindow->Create(m_WindowConfig);
		HSDebug::CheckResult(funcResult);

		return Result::None;
	}

	void HSGame::UpdateEngine()
	{
		if (m_AccTime < frameTime)
			return;

		m_InputLayer->UpdateKeyStates();

		m_AccTime = 0.0f;
	}
}
