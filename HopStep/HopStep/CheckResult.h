#pragma once
#include "HSDebug.h"
#include "Result.h"

namespace HopStep
{
	inline namespace Internal
	{
		struct ResultChecker
		{
			Result result = Result::None;

			ResultChecker& operator=(const Result& result)
			{
				HSDebug::CheckResult(result);
				this->result = result;
				return *this;
			}
		};
	}
}
