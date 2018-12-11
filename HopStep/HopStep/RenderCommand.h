#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		enum class RenderCommandType : int
		{
			None,
			ClearScreen
		};

		class RenderCommand
		{
		public :

			RenderCommandType type = RenderCommandType::None;
			std::chrono::milliseconds tickTimeStamp;
		};
	}
}
