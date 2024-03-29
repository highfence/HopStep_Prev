#pragma once
#include "../Extern/Jsoncpp/include/json/json.h"

namespace HopStep
{
	struct HSColor
	{
		HSColor() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
		HSColor(float value) : r(value), g(value), b(value), a(value) {}
		HSColor(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}

		static HSColor FromString(Json::Value& jsonColor);
		void ToString(Json::Value& root);

		float r;
		float g;
		float b;
		float a;
	};
}
