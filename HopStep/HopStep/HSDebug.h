#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		class HSDebug
		{
		public:

			static std::wstring GetResultName(Result result);
			static void CheckResult(Result result);
		};
	}
}
