#pragma once
#include "HSColor.h"
#include "HSRect.h"
#include "RenderCommandDefine.h"
#include "JsonSerialize.h"

namespace HopStep
{
	inline namespace Internal
	{
#pragma pack(push, 1)

		class RenderCommand
		{
		public :

			RenderCommandType type = RenderCommandType::None;
			// std::chrono::milliseconds tickTimeStamp;

			int bodySize = 0;
			char* body;
		};

#pragma pack(pop)

		class ClearScreenCommand final : public IJsonSerializable
		{
		public :
			ClearScreenCommand(void) {}
			virtual ~ClearScreenCommand(void) {}

			HSColor m_ScreenColor;
			bool m_IsColorChanged = false;

			virtual void Serialize(Json::Value& root) override;
			virtual void Deserialize(Json::Value& root) override;
		};

		class DrawRectCommand final : public IJsonSerializable
		{
		public:

			DrawRectCommand(void) {}
			virtual ~DrawRectCommand(void) {}

			HSRect m_Rect;

			virtual void Serialize(Json::Value& root) override;
			virtual void Deserialize(Json::Value& root) override;
		};
	}

}
