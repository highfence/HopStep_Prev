#include "stdafx.h"
#include "InputLayer.h"

namespace HopStep
{
	std::shared_ptr<InputLayer> InputLayer::instance = nullptr;

	std::shared_ptr<InputLayer> InputLayer::Get()
	{
		if (instance == nullptr)
			instance = std::make_shared<InputLayer>();

		return instance;
	}

	InputLayer::~InputLayer()
	{
	}

	void InputLayer::UpdateKeyStates()
	{
		if (GetKeyboardState(m_Keys))
		{
			for (int i = 0; i < keyboardNumber; ++i)
			{
				// 현재 키입력이 있는 경우.
				if (m_Keys[i] & 0x80)
				{
					// 그 전 키입력이 없었다면 시작상태로 만들어준다 (PUSHKEY)
					if (!m_OldKeys[i])
					{
						m_OldKeys[i] = 1;
						m_Keys[i] |= 0x40;
					}
					// 아니라면 그냥 누르고 있는 중 (HOLDKEY)
				}
				// 키입력이 현재 없는 경우.
				else
				{
					// 그 전 키입력이 없었다면 띄는 상태로 만들어준다. (PULLKEY)
					if (m_OldKeys[i])
					{
						m_OldKeys[i] = 0;
						m_Keys[i] = 0x20;
					}
					// 아니라면 그냥 안누르고 있는 상태.
					else
					{
						m_Keys[i] = 0x10;
					}
				}
			}
		}
	}

	KeyState InputLayer::GetKeyState(int keyIndex)
	{
		if (keyIndex < 0 || keyIndex >= keyboardNumber)
			return KeyState::None;

		auto keyState = m_Keys[keyIndex];

		switch (keyState)
		{
		case FREEKEY :
			return KeyState::FreeKey;
		case PULLKEY :
			return KeyState::PullKey;
		case PUSHKEY :
			return KeyState::PushKey;
		case HOLDKEY :
			return KeyState::HoldKey;

		default :
			return KeyState::None;
		}
	}
}
