#pragma once
#include "../Extern/json/json.h"

namespace HopStep
{
	__interface IJsonSerializable
	{
	public:
		virtual void Serialize(Json::Value& root) = 0;
		virtual void Deserialize(Json::Value& root) = 0;
	};

	class JsonSerializer
	{
	public:
		static bool Serialize(IJsonSerializable* pObj, std::string& output);
		static bool Deserialize(IJsonSerializable* pObj, std::string& input);

	private:
		JsonSerializer(void) {};
	};
}
