#pragma once
#include <stack>
#include "IScene.h"

namespace HopStep
{
	class HSGame
	{
	public:

		void GameStart();

		void SetStartScene(IScene* startScene);

	private :

		std::stack<std::shared_ptr<IScene*>> m_Scene;

	};
}
