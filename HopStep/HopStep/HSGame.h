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
#include "InputLayer.h"

namespace HopStep
{
	class HSGame
	{
	public:

		HSGame();
		~HSGame();

		void Release();

		void GameStart();

		void SetWindowConfig(WindowConfig& config);

		void SetStartScene(std::shared_ptr<IScene> startScene);

	private :

		Result InitEngine();
		Result InitRenderQueue();
		Result InitRenderer();
		Result OpenWindow();

		void UpdateEngine();
		WindowConfig m_WindowConfig;

		std::stack<std::shared_ptr<IScene>> m_Scene;
		std::unique_ptr<HSWindow> m_GameWindow;
		std::unique_ptr<GameTimer> m_Timer;
		std::shared_ptr<InputLayer> m_InputLayer;
		std::unique_ptr<IRenderer> m_Renderer;
		
		using RenderCommandPool = Pool<RenderCommand>;
		using RenderQueue = SwapContainer<RenderCommandPool>;
		std::shared_ptr<RenderQueue> m_RenderQueue;

		std::thread m_RenderThread;
		std::atomic_bool m_IsRenderThreadActive = false;
		void RenderThreadWork();

		float m_AccTime = 0.0f;
	};
}
