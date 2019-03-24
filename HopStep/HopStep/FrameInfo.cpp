#include "stdafx.h"
#include "FrameInfo.h"

namespace HopStep
{
	bool Internal::FrameInfo::IsValid()
	{
		if (m_RenderCommands.size() == 0)
			return false;

		return true;
	}

	void Internal::FrameInfo::AddRenderCommand(RenderCommand& command)
	{
		if (m_RenderCommands.find(command.type) == m_RenderCommands.end())
		{
			std::vector<RenderCommand> commandList;
			m_RenderCommands.emplace(command.type, commandList);
		}

		auto typeIter = m_RenderCommands.find(command.type);
		typeIter->second.push_back(command);
	}
}
