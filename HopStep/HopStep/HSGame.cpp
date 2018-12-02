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
		m_IsRenderThreadActive = false;
		m_RenderThread.join();

		while (m_Scene.empty() == false)
			m_Scene.pop();
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

	Result HSGame::InitEngine()
	{
		m_Scene.empty();

		m_Timer = std::make_unique<GameTimer>();
		m_Timer->InitTimer();

		HSDebug::CheckResult(InitRenderQueue());

		m_GameWindow = std::make_unique<HSWindow>();

		m_InputLayer = std::make_shared<InputLayer>();

		return Result::None;
	}

	// Todo : make fetch this poolsize from engine config
	constexpr int basicRenderCommandPoolSize = 1024;
	Result HSGame::InitRenderQueue()
	{
		auto firstPool = new RenderCommandPool();
		if (firstPool == nullptr)
			return Result::InitializeFailed;

		firstPool->Init(basicRenderCommandPoolSize);

		auto secondPool = new RenderCommandPool();
		if (secondPool == nullptr)
			return Result::InitializeFailed;

		secondPool->Init(basicRenderCommandPoolSize);

		m_RenderQueue = std::make_shared<RenderQueue>(firstPool, secondPool);

		return Result::None;
	}

	Result HSGame::InitRenderer()
	{
		 m_IsRenderThreadActive = true;
		 m_RenderThread = std::thread([this]() { RenderThreadWork(); });

		return Result::None;
	}

	Result HSGame::OpenWindow()
	{
		HSDebug::CheckResult(m_GameWindow->Create(m_WindowConfig));

		return Result::None;
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
		std::unique_ptr<IRenderer> renderer;
		// Todo : Renderer initialize with engine config
		renderer = std::make_unique<DX2DRenderer>();

		Result renderThreadResult;

		renderThreadResult = renderer->SetRenderQueue(m_RenderQueue);
		HSDebug::CheckResult(renderThreadResult);

		renderThreadResult = renderer->InitRenderer();
		HSDebug::CheckResult(renderThreadResult);

		while (m_IsRenderThreadActive)
		{
			renderer->Render();
		}
	}
}
