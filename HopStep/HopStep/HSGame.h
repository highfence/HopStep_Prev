#pragma once
#include <stack>
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

		void SetStartScene(IScene* startScene);

	private :

		Result InitEngine();
		Result InitRenderQueue();
		Result InitRenderer();
		Result OpenWindow();

		void UpdateEngine();
		WindowConfig m_WindowConfig;

		std::stack<IScene*> m_Scene;
		std::unique_ptr<HSWindow> m_GameWindow;
		std::unique_ptr<GameTimer> m_Timer;
		std::shared_ptr<InputLayer> m_InputLayer;
		
		using RenderCommandPool = Pool<RenderCommand>;
		using RenderQueue = SwapContainer<RenderCommandPool>;
		std::shared_ptr<RenderQueue> m_RenderQueue;

		float m_AccTime = 0.0f;
	};
}
