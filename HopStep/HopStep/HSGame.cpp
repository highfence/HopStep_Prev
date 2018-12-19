#include "stdafx.h"
#include "Timer.h"
#include "DX2DRenderer.h"
#include "HSConsoleLogger.h"
#include "HSGame.h"

namespace HopStep
{
	HSGame::HSGame()
	{
		if (thisGame != nullptr)
		{
			HSDebug::CheckResult(Result::DuplicatedGameInstance);
			thisGame = this;
		}
	}

	HSGame::~HSGame()
	{
		Release();

		m_RenderThread.join();
	}

	void HSGame::Release()
	{
		while (m_Scene.empty() == false)
			m_Scene.pop();

		m_IsRenderThreadActive = false;
	}

	void HSGame::GameStart()
	{
		auto startScene = m_Scene.top();
		if (startScene == nullptr)
			return;

		startScene->Init();

		UpdateMessageLoop();
	}

	void HSGame::SetWindowConfig(WindowConfig& config)
	{
		m_WindowConfig = config;
	}

	void HSGame::SetStartScene(std::shared_ptr<IScene> startScene)
	{
		if (startScene == nullptr)
			return;

		m_Scene.push(startScene);
	}

	void HSGame::InitEngine()
	{
		ResultChecker funcResult;
		m_Scene.empty();

		m_Logger = std::make_unique<HSConsoleLogger>();

		m_RenderObjectList = RenderProducerList::Get();
		m_TickObjectList = TickObjectList::Get();

		m_RenderQueue = std::make_unique<RenderQueue>();

		m_Timer = std::make_unique<GameTimer>();
		m_Timer->InitTimer();

		m_GameWindow = std::make_unique<HSWindow>(m_Logger.get());
		OpenWindow();

		funcResult = InitRenderer();

		m_InputLayer = std::make_unique<InputLayer>();
	}

	Result HSGame::InitRenderer()
	{
		// Todo : Renderer initialize with engine config
		m_Renderer = std::make_unique<DX2DRenderer>();

		ResultChecker renderThreadResult;
		renderThreadResult = m_Renderer->SetRenderQueue(m_RenderQueue.get());
		renderThreadResult = m_Renderer->InitRenderer(m_GameWindow.get()->WindowHandle, m_Logger.get());

		m_IsRenderThreadActive = true;
		m_RenderThread = std::thread([&]() { RenderThreadWork(); });

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
		m_Timer->ProcessTime();

		while (true)
		{
			static float deltaTime = m_Timer->GetElapsedTime();
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

		m_InputLayer->UpdateKeyStates();

		m_TickObjectList->ProcessTick(m_AccTime);

		auto currentFrame = std::make_shared<FrameInfo>();

		m_RenderObjectList->GatherCommand(currentFrame);

		if (currentFrame->IsValid())
			PushToRenderQueue(currentFrame);

		m_AccTime = 0.0f;
	}

	void HSGame::PushToRenderQueue(std::shared_ptr<FrameInfo> frameInfo)
	{
		if (frameInfo == nullptr)
			return;

		int queueSize = m_RenderQueue->Size();
		if (queueSize >= 60)
		{
			m_RenderQueue->Clear();
		}

		m_RenderQueue->Push(frameInfo);
	}

	void HSGame::RenderThreadWork()
	{
		while (m_IsRenderThreadActive)
		{
			m_Renderer->Render();
		}

		m_Renderer->ReleaseRenderer();
	}
}
