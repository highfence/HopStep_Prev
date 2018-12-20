#pragma once
#include "Keys.h"

namespace HopStep
{
	// Todo : Make Input Message to queue
	class InputLayer
	{
	public:

		static std::shared_ptr<InputLayer> Get();

		InputLayer() = default;
		~InputLayer();

		void UpdateKeyStates();

		KeyState GetKeyState(int keyIndex);

	private :

		BYTE m_Keys[keyboardNumber];
		BYTE m_OldKeys[keyboardNumber];

		static std::shared_ptr<InputLayer> instance;
	};
}
