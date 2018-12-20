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
				// ���� Ű�Է��� �ִ� ���.
				if (m_Keys[i] & 0x80)
				{
					// �� �� Ű�Է��� �����ٸ� ���ۻ��·� ������ش� (PUSHKEY)
					if (!m_OldKeys[i])
					{
						m_OldKeys[i] = 1;
						m_Keys[i] |= 0x40;
					}
					// �ƴ϶�� �׳� ������ �ִ� �� (HOLDKEY)
				}
				// Ű�Է��� ���� ���� ���.
				else
				{
					// �� �� Ű�Է��� �����ٸ� ��� ���·� ������ش�. (PULLKEY)
					if (m_OldKeys[i])
					{
						m_OldKeys[i] = 0;
						m_Keys[i] = 0x20;
					}
					// �ƴ϶�� �׳� �ȴ����� �ִ� ����.
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
