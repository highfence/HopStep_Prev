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

		void PushScene(IScene* scene)
		{
			m_Scenes.push(scene);
		}

		void PopScene()
		{
			m_Scenes.pop();
		}

		IScene* Peek()
		{
			return m_Scenes.top();
		}

	protected :

		std::stack<IScene*> m_Scenes;
	};
}
