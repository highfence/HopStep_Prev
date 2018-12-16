#include "stdafx.h"
#include "HSConsoleLogger.h"
#include "RenderCommandProcessor.h"


namespace HopStep
{
	Result Internal::RenderCommandProcessor::Init(HSConsoleLogger * logger)
	{
		if (logger == nullptr)
			return Result::NullParameter;

		m_Logger = logger;

		return Result::None;
	}

	Result Internal::RenderCommandProcessor::Process(std::shared_ptr<FrameInfo> frameInfo)
	{
		if (frameInfo == nullptr)
			return Result::NullParameter;

		const auto& commands = frameInfo->m_RenderCommands;

		for (auto& commandList : commands)
		{
			auto commandType = commandList.first;
			auto renderFunction = m_RenderFunctionMap.find(commandType);

			if (renderFunction == m_RenderFunctionMap.end())
			{
				m_Logger->Write(LogType::Warn, "%s | Unregisted function render type : %d", __FUNCTION__, static_cast<int>(commandType));
				continue;
			}

			for (auto& command : commandList.second)
			{ 
				renderFunction->second(command);
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
