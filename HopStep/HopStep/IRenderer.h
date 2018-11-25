#pragma once

namespace HopStep
{
	inline namespace Internal
	{
		__interface IRenderer
		{
			FactoryClass Factory
			{
				static IRenderer* GetRenderer();
			};
		};
	}
}
