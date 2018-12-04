#pragma once
#include <memory>
#include <atomic>
#include <utility>
#include <unordered_map>
#include "GameObject.h"

namespace HopStep
{
	class ObjectManager
	{
	public:

		ObjectManager() = delete;
		~ObjectManager() { instance == nullptr; }

		static std::shared_ptr<ObjectManager> Get();

		Result RegistObject(GameObject* object);
		Result ReleaseObject(GameObject* object);

		Result ClearAllObject();

	private :

		using GameObjectPtr = std::shared_ptr<GameObject>;
		std::unordered_map<ObjectId, GameObjectPtr> m_ObjectMap;

		static std::shared_ptr<ObjectManager> instance;
	};
}

