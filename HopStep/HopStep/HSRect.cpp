#include "stdafx.h"
#include "FrameInfo.h"
#include "HSRect.h"

namespace HopStep
{
	HSRect & HSRect::operator=(const HSRect & rhs)
	{
		this->m_Center = rhs.m_Center;
		this->m_Height = rhs.m_Height;
		this->m_Width = rhs.m_Width;
		this->m_RectColor = rhs.m_RectColor;
		this->m_Type = rhs.m_Type;

		return *this;
	}

	void HSRect::Produce(FrameInfo* frameInfo)
	{
		if (frameInfo == nullptr)
			return;

		DrawRectCommand command;
		command.m_Rect = HSRect(*this);

		std::string jsonString;
		JsonSerializer::Serialize(&command, jsonString);

		auto renderCommand = std::make_shared<RenderCommand>();

		char* body = new char[jsonString.size() + 1];
		std::copy(jsonString.begin(), jsonString.end(), body);
		body[jsonString.size()] = '\0';

		renderCommand->body = body;
		renderCommand->bodySize = jsonString.size();

		renderCommand->type = RenderCommandType::DrawRect;

		frameInfo->AddRenderCommand(renderCommand);
	}
}
