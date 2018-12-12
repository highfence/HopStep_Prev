#pragma once

namespace HopStep
{
#pragma pack(push, 1)

	inline namespace Internal
	{
		enum class RenderCommandType : int
		{
			None,
			ClearScreen
		};

		class RenderCommandHeader
		{
		public :

			RenderCommandType type = RenderCommandType::None;
			std::chrono::milliseconds tickTimeStamp;

			int bodySize = 0;
			char* body;
		};

		class RenderCommand
		{
		public :
		};
	}

#pragma push
}
