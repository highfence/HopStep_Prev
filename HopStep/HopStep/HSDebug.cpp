#include "stdafx.h"
#include "HopStep.h"
#include "HSDebug.h"


namespace HopStep
{
	std::wstring HSDebug::GetResultName(Result result)
	{
		switch (result)
		{
		case Result::None:
			return std::wstring(TEXT("None."));
		case Result::InvalidParameter:
			return std::wstring(TEXT("Invalid parameter."));
		case Result::NullParameter:
			return std::wstring(TEXT("Parameter is null."));
		case Result::WindowClassRegistFailed:
			return std::wstring(TEXT("Window registration failed!"));
		case Result::WindowInvalidHandleReturn:
			return std::wstring(TEXT("Window creation failed!"));

		default:
			return std::wstring(TEXT("Undefined result enum."));
		}
	}

	void HSDebug::CheckResult(Result result)
	{
		if (result == Result::None)
			return;

		std::wstring resultName = GetResultName(result);
		std::wstring boxText = TEXT("Error! Result : ");
		boxText.append(resultName);

		const TCHAR* errorMsg = boxText.c_str();
		const TCHAR* caption = TEXT("Error!");

		MessageBox(NULL, errorMsg, caption, MB_OK);

		__debugbreak();
	}
}
