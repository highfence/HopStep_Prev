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

			// Todo : change to template function (using boost::shared_ptr<T>)
			void AddRenderCommand(RenderCommandType type, std::shared_ptr<RenderCommand> command)
			{
				if (command == nullptr)
					return;

				if (m_RenderCommands.find(type) == m_RenderCommands.end())
				{
					std::vector<std::shared_ptr<RenderCommand>> commandList;
					m_RenderCommands.emplace(type, commandList);
				}

				auto list = m_RenderCommands[type];
				list.push_back(command);
			}

			std::unordered_map<RenderCommandType, std::vector<std::shared_ptr<RenderCommand>>> m_RenderCommands;
		};
	}
}
