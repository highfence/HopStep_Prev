#pragma once

namespace HopStep
{
	struct HSColor
	{
		HSColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		std::wstring ToString() const;
		static HSColor FromString(Json::Value& jsonColor);

		float r;
		float g;
		float b;
		float a;
	};
}
