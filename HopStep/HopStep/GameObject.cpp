#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"

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
	}
}