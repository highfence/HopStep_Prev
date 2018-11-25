#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		enum class Result
		{
			None = 0,

			InvalidParameter = 1,

			WindowClassRegistFailed = 20,
			WindowInvalidHandleReturn = 21,

			ResultMaxCount
		};
	}
}
