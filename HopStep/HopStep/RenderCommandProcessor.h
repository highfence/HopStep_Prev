#pragma once
#include <unordered_map>
#include "FrameInfo.h"
#include "RenderCommandDefine.h"
#include "RenderCommand.h"

namespace HopStep
{
	inline namespace Internal
	{
		using RenderCommandFunc = std::function<void(std::shared_ptr<RenderCommandHeader>)>;

		class RenderCommandProcessor
		{
		public:

			RenderCommandProcessor() {}
			~RenderCommandProcessor() {}

			Result Init(HSConsoleLogger* logger);

			Result Process(std::shared_ptr<FrameInfo> frameInfo);

			Result RegistRenderFunction(RenderCommandType type, RenderCommandFunc function);;

		private :

			HSConsoleLogger* m_Logger = nullptr;

			std::unordered_map<RenderCommandType, RenderCommandFunc> m_RenderFunctionMap;
		};
	}
}
