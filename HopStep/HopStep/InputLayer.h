#pragma once
#include "Keys.h"

namespace HopStep
{
	// Todo : Make Input Message to queue
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
