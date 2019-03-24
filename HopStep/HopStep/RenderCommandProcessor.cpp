#include "stdafx.h"
#include "HSConsoleLogger.h"
#include "RenderCommandProcessor.h"


namespace HopStep
{
	Result Internal::RenderCommandProcessor::Init(HSConsoleLogger * logger)
	{
		m_Logger = logger;

		return Result::None;
	}

	Result Internal::RenderCommandProcessor::Process(FrameInfo& frameInfo)
	{
		for (auto& commandList : frameInfo.m_RenderCommands)
		{
			auto commandType = commandList.first;
			auto renderFunctionIter = m_RenderFunctionMap.find(commandType);

			if (renderFunctionIter == m_RenderFunctionMap.end())
			{
				m_Logger->Write(LogType::Warn, "%s | Unresisted function render type : %d", __FUNCTION__, static_cast<int>(commandType));
				continue;
			}

			RenderCommandFunc renderFunction = renderFunctionIter->second;

			for (RenderCommand command : commandList.second)
			{ 
				renderFunction(command);
			}
		}

		return Result::None;
	}

	Result Internal::RenderCommandProcessor::RegistRenderFunction(RenderCommandType type, RenderCommandFunc function)
	{
		if (m_RenderFunctionMap.find(type) != m_RenderFunctionMap.end())
		{
			m_Logger->Write(LogType::Warn, "%s | RenderCommand process function must correspond to one type each : Duplicated type(%d)", __FUNCTION__, static_cast<int>(type));
			return Result::DuplicatedId;
		}

		m_RenderFunctionMap.emplace(type, function);

		return Result::None;
	}
}
