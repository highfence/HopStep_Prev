#include "stdafx.h"
#include "HSColor.h"

namespace HopStep
{
	std::wstring HSColor::ToString() const
	{
		Json::Value root;
		root["r"] = r;
		root["g"] = g;
		root["b"] = b;
		root["a"] = a;

		std::string jsonString = root.asString();
		return StringHelper::WstringFromString(jsonString);
	}

	HSColor HSColor::FromString(Json::Value & jsonColor)
	{
		float r, g, b, a;
		r = jsonColor.get("r", 0.0f).asFloat();
		g = jsonColor.get("g", 0.0f).asFloat();
		b = jsonColor.get("b", 0.0f).asFloat();
		a = jsonColor.get("a", 0.0f).asFloat();

		return HSColor(r, g, b, a);
	}
}
