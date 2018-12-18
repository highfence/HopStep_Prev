#include "stdafx.h"
#include "RenderCommand.h"

namespace HopStep
{
	void Internal::ClearScreenCommand::Serialize(Json::Value & root)
	{
		m_ScreenColor.ToString(root);
		root["IsColorChanged"] = m_IsColorChanged;
	}

	void Internal::ClearScreenCommand::Deserialize(Json::Value & root)
	{
		m_ScreenColor = HSColor::FromString(root);
		m_IsColorChanged = root["IsColorChanged"].asBool();
	}

	void Internal::DrawRectCommand::Serialize(Json::Value & root)
	{
	}

	void Internal::DrawRectCommand::Deserialize(Json::Value & root)
	{
	}
}
