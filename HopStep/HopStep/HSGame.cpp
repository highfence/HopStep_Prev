#include "stdafx.h"
#include "Timer.h"
#include "DX2DRenderer.h"
#include "HSGame.h"

namespace HopStep
{
	HSGame::HSGame()
	{
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

	constexpr float frameTime = 1.0f / 60.0f;
	void HSGame::GameStart()
	{
		MSG message;
		while (true)
		{
			m_Timer->ProcessTime();
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

		m_RenderQueue = std::make_unique<RenderQueue>();

		m_Timer = std::make_unique<GameTimer>();
		m_Timer->InitTimer();

		m_GameWindow = std::make_unique<HSWindow>(m_Logger.get());
		OpenWindow();

		funcResult = InitRenderer();

		m_InputLayer = std::make_shared<InputLayer>();
	}

	Result HSGame::InitRenderer()
	{
		// Todo : Renderer initialize with engine config
		m_Renderer = std::make_unique<DX2DRenderer>();

		Result renderThreadResult;

		renderThreadResult = m_Renderer->SetRenderQueue(m_RenderQueue.get());
		HSDebug::CheckResult(renderThreadResult);

		renderThreadResult = m_Renderer->InitRenderer(m_GameWindow.get()->WindowHandle);
		HSDebug::CheckResult(renderThreadResult);

		m_IsRenderThreadActive = true;
		m_RenderThread = std::thread([&]() { RenderThreadWork(); });
		//m_RenderThread.detach();

		return Result::None;
	}

	Result HSGame::OpenWindow()
	{
		ResultChecker openResult;
		openResult = m_GameWindow->Create(m_WindowConfig);

		return openResult.result;
	}

	void HSGame::UpdateEngine()
	{
		if (m_AccTime < frameTime)
			return;

		m_InputLayer->UpdateKeyStates();

		m_AccTime = 0.0f;
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
