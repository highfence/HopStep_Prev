#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		enum class Result
		{
			None = 0,

			InvalidParameter = 1,
			NullParameter = 2,
			GetSingletonFailed = 3,
			DuplicatedId = 4,

			InitializeFailed = 10,

			WindowClassRegistFailed = 20,
			WindowInvalidHandleReturn = 21,

			ResultMaxCount
		};
	}
}
