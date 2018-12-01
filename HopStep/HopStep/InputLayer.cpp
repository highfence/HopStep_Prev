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
}
