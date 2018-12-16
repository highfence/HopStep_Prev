#pragma once
#include "../Extern/json/json.h"

namespace HopStep
{
	struct HSColor
	{
		HSColor() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
		HSColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		static HSColor FromString(Json::Value& jsonColor);
		void ToString(Json::Value& root);

		float r;
		float g;
		float b;
		float a;
	};
}
