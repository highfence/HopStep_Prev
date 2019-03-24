#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "IComponent.h"

namespace HopStep
{
	GameObject::GameObject()
	{
		auto objManager = ObjectManager::Get();
		if (objManager == nullptr)
		{
			HSDebug::CheckResult(Result::GetSingletonFailed);
			return;
		}

		objManager->RegistObject(this);
	}

	GameObject::~GameObject()
	{
		auto objManager = ObjectManager::Get();
		if (objManager == nullptr)
		{
			HSDebug::CheckResult(Result::GetSingletonFailed);
			return;
		}

		objManager->ReleaseObject(this);
	}

	void GameObject::Tick(const float deltaTime)
	{
		for (auto component : m_Components)
		{
			component->Tick(deltaTime);
		}
	}

	bool GameObject::AddComponent(IComponent * component)
	{
		if (component == nullptr)
			return false;

		// Todo : 컴포넌트 순회가 빨라서 vector로 하고 있긴 하지만. 
		// 중복 컴포넌트를 허용하지 않을 경우 다른 자료구조로 처리할 필요 있음.
		m_Components.emplace_back(component);

		return true;
	}

	bool GameObject::RemoveComponent(IComponent * component)
	{
		if (component == nullptr)
			return false;

		if (std::find(m_Components.begin(), m_Components.end(), component) == m_Components.end())
			return false;

		std::remove(m_Components.begin(), m_Components.end(), component);
		return true;
	}
}