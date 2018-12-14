#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		template<class Interface>
		inline void SafeRelease(Interface **ppInterfaceToRelease)
		{
			if (*ppInterfaceToRelease != nullptr)
			{
				(*ppInterfaceToRelease)->Release();
				(*ppInterfaceToRelease) = nullptr;
			}
		}
	}
}

