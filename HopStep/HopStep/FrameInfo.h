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

			bool IsValid() 
			{
				if (m_RenderCommands.size() == 0)
					return false;

				return true;
			}

			// Todo : change to template function (using boost::shared_ptr<T>)
			void AddRenderCommand(std::shared_ptr<RenderCommand> command)
			{
				if (command == nullptr)
					return;

				if (m_RenderCommands.find(command->type) == m_RenderCommands.end())
				{
					std::vector<std::shared_ptr<RenderCommand>> commandList;
					m_RenderCommands.emplace(command->type, commandList);
				}

				auto typeIter = m_RenderCommands.find(command->type);
				typeIter->second.emplace_back(command);
			}

			std::unordered_map<RenderCommandType, std::vector<std::shared_ptr<RenderCommand>>> m_RenderCommands;
		};
	}
}
