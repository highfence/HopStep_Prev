#pragma once
#include <memory>
#include <stack>
#include "IScene.h"

namespace HopStep
{
	class SceneManager
	{
	public:
		
		SceneManager() = default;
		virtual ~SceneManager() { ClearScenes(); }

		void ClearScenes()
		{
			while (m_Scenes.empty() == false)
				m_Scenes.pop();
		}

		void PushScene(std::shared_ptr<IScene> scene)
		{
			m_Scenes.push(scene);
		}

		void PopScene()
		{
			m_Scenes.pop();
		}

		std::shared_ptr<IScene> Peek()
		{
			return m_Scenes.top();
		}

	protected :

		std::stack<std::shared_ptr<IScene>> m_Scenes;
	};
}
