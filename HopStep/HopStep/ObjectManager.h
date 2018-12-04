#pragma once
#include <memory>
#include <atomic>
#include <utility>
#include <vector>
#include "GameObject.h"

namespace HopStep
{
	class ObjectManager
	{
	public:

		~ObjectManager() { instance == nullptr; }

		static std::shared_ptr<ObjectManager> Get();

	private :

		using GameObjectPtr = std::shared_ptr<GameObject>;
		std::vector<GameObjectPtr> m_ObjectList;

		static std::shared_ptr<ObjectManager> instance;
	};
}

