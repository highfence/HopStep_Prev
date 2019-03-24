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

			bool IsValid();
			// Todo : change to template function (using boost::shared_ptr<T>)
			void AddRenderCommand(RenderCommand& command);

			std::unordered_map<RenderCommandType, std::vector<RenderCommand>> m_RenderCommands;
		};
	}
}
