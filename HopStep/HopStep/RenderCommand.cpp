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
		m_Rect.m_RectColor.ToString(root);

		root["centerX"] = m_Rect.m_Center.x;
		root["centerY"] = m_Rect.m_Center.y;
		root["type"   ] = static_cast<int>(m_Rect.m_Type);
		root["width"  ] = m_Rect.m_Width;
		root["height" ] = m_Rect.m_Height;
	}

	void Internal::DrawRectCommand::Deserialize(Json::Value & root)
	{
		m_Rect.m_RectColor = HSColor::FromString(root);

		m_Rect.m_Center.x = root["centerX"].asFloat();
		m_Rect.m_Center.y = root["centerY"].asFloat();
		m_Rect.m_Width    = root["width"].asFloat();
		m_Rect.m_Height   = root["height"].asFloat();
		m_Rect.m_Type     = static_cast<HSRect::RectType>(root["type"].asInt());
	}
}
