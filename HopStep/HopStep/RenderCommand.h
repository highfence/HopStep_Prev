#pragma once
#include "HSColor.h"
#include "ByteSerialize.h"
#include "RenderCommandDefine.h"

namespace HopStep
{
	inline namespace Internal
	{
#pragma pack(push, 1)

		class RenderCommandHeader
		{
		public :

			RenderCommandType type = RenderCommandType::None;
			std::chrono::milliseconds tickTimeStamp;

			int bodySize = 0;
			byte* body;
		};

#pragma pack(pop)

		class ClearScreenCommand 
		{
		public :
			ClearScreenCommand(void) {}
			virtual ~ClearScreenCommand(void) {}

			HSColor m_ScreenColor;
		};
	}

}
