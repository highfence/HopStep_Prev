#pragma once

namespace HopStep
{
	class StringHelper
	{
	public:

		static std::wstring WstringFromString(std::string& string);
		static std::string StringFromWstring(std::wstring& wstring);
	};
}
