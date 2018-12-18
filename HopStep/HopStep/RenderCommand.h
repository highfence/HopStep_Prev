#pragma once
#include "HSColor.h"
#include "ByteSerialize.h"
#include "RenderCommandDefine.h"
#include "HSVector.h"
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
			byte* body;
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

			enum class RectType : int
			{
				LineRect,
				FilledRect
			};

			DrawRectCommand(void) : m_Center(0.0f), m_Type(RectType::FilledRect) {}
			virtual ~DrawRectCommand(void) {}

			HSColor m_RectColor;
			HSVector<float> m_Center;
			RectType m_Type;
			float m_Width = 0.0f;
			float m_Height = 0.0f;

			virtual void Serialize(Json::Value& root) override;
			virtual void Deserialize(Json::Value& root) override;
		};
	}

}
