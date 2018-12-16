#pragma once
#include <unordered_map>
#include "RenderCommandDefine.h"
#include "RenderCommand.h"

namespace HopStep
{
	inline namespace Internal
	{
		class FrameInfo
		{
		public :

			std::unordered_map<RenderCommandType, RenderCommandHeader> m_RenderCommands;
		};
	}
}
