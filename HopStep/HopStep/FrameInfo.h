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

			std::unordered_map<RenderCommandType, std::vector<std::shared_ptr<RenderCommand>>> m_RenderCommands;
		};
	}
}
