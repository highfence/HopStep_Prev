#include "stdafx.h"
#include "Result.h"
#include "HSDebug.h"


namespace HopStep
{
	std::wstring HSDebug::GetResultName(Result result)
	{
#ifndef _DEBUG
		return std::wstring();
#endif

		switch (result)
		{
		case Result::None:
			return std::wstring(TEXT("None."));
		case Result::InvalidParameter:
			return std::wstring(TEXT("Invalid parameter."));
		case Result::NullParameter:
			return std::wstring(TEXT("Parameter is null."));
		case Result::InitializeFailed:
			return std::wstring(TEXT("Initialize Failed."));
		case Result::GetSingletonFailed:
			return std::wstring(TEXT("Singleton class Get Failed."));
		case Result::DuplicatedId:
			return std::wstring(TEXT("Duplicated UID."));
		case Result::NotInitializeYet:
			return std::wstring(TEXT("Object Not Initialized Yet."));
		case Result::WindowClassRegistFailed:
			return std::wstring(TEXT("Window registration failed!"));
		case Result::WindowInvalidHandleReturn:
			return std::wstring(TEXT("Window creation failed!"));
		case Result::DX2DRenderFactoryInitializeFailed:
			return std::wstring(TEXT("DirectX2D Render Factory initialize failed!"));
		case Result::DX2DRenderTargetCreateFailed:
			return std::wstring(TEXT("DirectX2D Render Target initialize failed!"));

		default:
			return std::wstring(TEXT("Undefined result enum."));
		}
	}

	void HSDebug::CheckResult(Result result)
	{
#ifndef _DEBUG
		return;
#endif
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
