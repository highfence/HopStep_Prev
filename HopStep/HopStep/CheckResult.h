#pragma once
#include "HSDebug.h"
#include "Result.h"

namespace HopStep
{
	inline namespace Internal
	{
		struct CheckResult
		{
			Result result = Result::None;

			CheckResult& operator=(const Result& result)
			{
				HSDebug::CheckResult(result);
				this->result = result;
				return *this;
			}
		};
	}
}
