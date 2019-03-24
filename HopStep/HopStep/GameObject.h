#pragma once
#include "TickObject.h"
#include <vector>

namespace HopStep
{
	using ObjectId = long long;
	class IComponent;

	class GameObject : public TickObject
	{
	public :

		GameObject();
		virtual ~GameObject();

		void SetObjectId(ObjectId id) { m_Id = id; }
		ObjectId GetId() const { return m_Id; }

		virtual void Tick(const float deltaTime);

		bool AddComponent(IComponent* component);
		bool RemoveComponent(IComponent* component);

	protected :

		std::vector<IComponent*> m_Components;

		ObjectId m_Id = 0L;
	};
}
