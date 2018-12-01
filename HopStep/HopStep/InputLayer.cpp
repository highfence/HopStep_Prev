#include "stdafx.h"
#include "InputLayer.h"

namespace HopStep
{
	InputLayer::InputLayer()
	{
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
}
