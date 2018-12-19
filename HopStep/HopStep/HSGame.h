#pragma once
#include <stack>
#include <thread>
#include <atomic>
#include "HSWindow.h"
#include "IScene.h"
#include "Result.h"
#include "Timer.h"
#include "IRenderer.h"
#include "SwapContainer.h"
#include "Pool.h"
#include "RenderCommand.h"
#include "RenderQueue.h"
#include "InputLayer.h"
#include "RenderProducerList.h"
#include "TickObjectList.h"
#include "HSConsoleLogger.h"

namespace HopStep
{
	class HSGame
	{
	public:

		HSGame();
		~HSGame();

		void InitEngine();

		void Release();

		void GameStart();

		void SetWindowConfig(WindowConfig& config);

		void SetStartScene(std::shared_ptr<IScene> startScene);

	private :

		Result InitRenderer();
		Result OpenWindow();

		void UpdateMessageLoop();
		void UpdateEngine();

		WindowConfig m_WindowConfig;

		std::stack<std::shared_ptr<IScene>> m_Scene;
		std::unique_ptr<HSWindow>           m_GameWindow;
		std::unique_ptr<GameTimer>          m_Timer;
		std::unique_ptr<InputLayer>         m_InputLayer;
		std::unique_ptr<IRenderer>          m_Renderer;
		std::unique_ptr<RenderQueue>        m_RenderQueue;
		std::unique_ptr<HSConsoleLogger>    m_Logger;

		std::shared_ptr<RenderProducerList> m_RenderObjectList;
		std::shared_ptr<TickObjectList>		m_TickObjectList;

		std::thread m_RenderThread;
		std::atomic_bool m_IsRenderThreadActive = false;
		void RenderThreadWork();

		float m_AccTime = 0.0f;
	};

	static HSGame* thisGame = nullptr;
}
