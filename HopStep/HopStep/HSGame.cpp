#include "stdafx.h"
#include "Timer.h"
#include "DX2DRenderer.h"
#include "HSConsoleLogger.h"
#include "HSGame.h"

namespace HopStep
{
	HSGame::HSGame()
	{
		if (globalGamePtr != nullptr)
		{
			HSDebug::CheckResult(Result::DuplicatedGameInstance);
			globalGamePtr = this;
		}
	}

	HSGame::~HSGame()
	{
		Release();

#ifdef HS_RENDER_THREAD
		m_RenderThread.join();
#endif
	}

	void HSGame::Release()
	{
		m_IsRenderThreadActive = false;
	}

	void HSGame::GameStart()
	{
		auto startScene = m_SceneManager->Peek();
		if (startScene == nullptr)
			return;

		startScene->Init();

		UpdateMessageLoop();
	}

	void HSGame::SetStartScene(IScene* startScene)
	{
		m_SceneManager->PushScene(startScene);
	}

	void HSGame::InitEngine(WindowConfig& config)
	{
		m_WindowConfig = config;

		ResultChecker funcResult;

		m_Logger = std::make_unique<HSConsoleLogger>();

		m_RenderObjectList = RenderProducerList::Get();
		m_TickObjectList = TickObjectList::Get();

		m_RenderQueue = std::make_unique<RenderQueue>();

		m_Timer = std::make_unique<GameTimer>();
		m_Timer->InitTimer();

		m_GameWindow = std::make_unique<HSWindow>(m_Logger.get());
		OpenWindow();

		funcResult = InitRenderer();

		m_SceneManager = std::make_unique<SceneManager>();
	}

	Result HSGame::InitRenderer()
	{
		// Todo : Renderer initialize with engine config
		m_Renderer = std::make_unique<DX2DRenderer>();

		ResultChecker renderThreadResult;
		renderThreadResult = m_Renderer->SetRenderQueue(m_RenderQueue.get());
		renderThreadResult = m_Renderer->InitRenderer(m_GameWindow.get()->WindowHandle, m_Logger.get());

#ifdef HS_RENDER_THREAD
		m_IsRenderThreadActive = true;
		m_RenderThread = std::thread([&]() { RenderThreadWork(); });
#endif

		return renderThreadResult.result;
	}

	Result HSGame::OpenWindow()
	{
		ResultChecker openResult;
		openResult = m_GameWindow->Create(m_WindowConfig);

		return openResult.result;
	}

	void HSGame::UpdateMessageLoop()
	{
		MSG message;

		float deltaTime = 0.0f;
		while (true)
		{
			m_Timer->ProcessTime();
			deltaTime = m_Timer->GetElapsedTime();
			m_AccTime += deltaTime;

			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
				{
					Release();
					break;
				}

				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				UpdateEngine();
			}
		}
	}

	// Todo : Load frameTime from engine(or game) config...
	constexpr float frameTime = 1.0f / 60.0f;
	void HSGame::UpdateEngine()
	{
		if (m_AccTime < frameTime)
			return;

		InputLayer::Get()->UpdateKeyStates();

		auto currentScene = m_SceneManager->Peek();
		if (currentScene != nullptr)
		{
			currentScene->UpdateScene(m_AccTime);
		}

		m_TickObjectList->ProcessTick(m_AccTime);

		FrameInfo currentFrame;

		m_RenderObjectList->GatherCommand(currentFrame);

		if (currentFrame.IsValid())
		{
			m_RenderQueue->Push(currentFrame);
#ifndef HS_RENDER_THREAD
			m_Renderer->Render();
#endif
		}

		m_AccTime = 0.0f;
	}

	void HSGame::RenderThreadWork()
	{
		GameTimer timer;
		timer.InitTimer();
		float accTime = 0.0f;

		while (m_IsRenderThreadActive)
		{
			timer.ProcessTime();
			accTime += timer.GetElapsedTime();

			if (accTime > frameTime)
			{
				m_Renderer->Render();
				accTime = 0.0f;
			}
		}

		m_Renderer->ReleaseRenderer();
	}
}
