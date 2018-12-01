#pragma once
#include "Keys.h"

namespace HopStep
{
	class InputLayer
	{
	public:
		InputLayer();
		~InputLayer();

		void UpdateKeyStates();

		KeyState GetKeyState(int keyIndex);

	private :

		BYTE m_Keys[keyboardNumber];
		BYTE m_OldKeys[keyboardNumber];
	};
}
