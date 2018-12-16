#pragma once
#include "stdafx.h"
#include "JsonSerialize.h"

namespace HopStep
{
	bool JsonSerializer::Serialize(IJsonSerializable * pObj, std::string & output)
	{
		if (pObj == NULL)
			return false;

		Json::Value serializeRoot;
		pObj->Serialize(serializeRoot);

		Json::StreamWriterBuilder writer;
		output = Json::writeString(writer, serializeRoot);

		return true;
	}

	bool JsonSerializer::Deserialize(IJsonSerializable * pObj, std::string & input)
	{
		if (pObj == NULL)
			return false;

		Json::Value deserializeRoot;
		Json::CharReaderBuilder builder;
		Json::CharReader* reader = builder.newCharReader();
		std::string errors;

		bool parseSucceed = reader->parse(input.c_str(), input.c_str() + input.size(), &deserializeRoot, &errors);

		if (parseSucceed)
			pObj->Deserialize(deserializeRoot);

		delete reader;
		return parseSucceed;
	}
}
