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

		// Todo : ������Ʈ ��ȸ�� ���� vector�� �ϰ� �ֱ� ������. 
		// �ߺ� ������Ʈ�� ������� ���� ��� �ٸ� �ڷᱸ���� ó���� �ʿ� ����.
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