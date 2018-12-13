#include "stdafx.h"
#include "StringHelper.h"

namespace HopStep
{
	std::wstring StringHelper::WstringFromString(std::string & string)
	{
		std::wstring wstring;
		wstring.assign(string.begin(), string.end());
		return wstring;
	}

	std::string StringHelper::StringFromWstring(std::wstring & wstring)
	{
		std::string string;
		string.assign(wstring.begin(), wstring.end());
		return string;
	}
}
