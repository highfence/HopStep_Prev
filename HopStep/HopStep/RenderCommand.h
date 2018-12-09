#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		enum class RenderCommandType : int
		{
			None,
			ResizeWindow,
		};

		class RenderCommand
		{
		public :

			RenderCommandType type = RenderCommandType::None;
		};
	}
}
