#include "stdafx.h"
#include "RenderCommand.h"

namespace HopStep
{
	bool Internal::CJsonSerializer::Serialize(IJsonSerializable * pObj, std::string & output)
	{
		if (pObj == NULL)
			return false;

		Json::Value serializeRoot;
		pObj->Serialize(serializeRoot);

		Json::StyledWriter writer;
		output = writer.write(serializeRoot);

		return true;
	}

	bool Internal::CJsonSerializer::Deserialize(IJsonSerializable * pObj, std::string & input)
	{
		if (pObj == NULL)
			return false;

		Json::Value deserializeRoot;
		Json::Reader reader;

		if (!reader.parse(input, deserializeRoot))
			return false;

		pObj->Deserialize(deserializeRoot);

		return true;
	}

	void Internal::ClearScreenCommand::Serialize(Json::Value & root)
	{
	}

	void Internal::ClearScreenCommand::Deserialize(Json::Value & root)
	{
	}
}
