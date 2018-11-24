#include "stdafx.h"
#include "HSGame.h"

namespace HopStep
{
	void HSGame::GameStart()
	{
		MSG message;

		while (true)
		{
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
					break;
			}
			else
			{
				// whole game update
			}
		}
	}

	void HSGame::SetStartScene(IScene * startScene)
	{
		if (startScene == nullptr)
			return;

		m_Scene.empty();
		m_Scene.push(std::make_shared<IScene*>(startScene));
	}
}
