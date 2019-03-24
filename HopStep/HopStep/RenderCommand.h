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

		template <class T>
		std::shared_ptr<T> Deserialze(RenderCommand& rawCommand)
		{
			std::shared_ptr<T> command = std::make_shared<T>();
			const int bodySize = rawCommand.bodySize;
			std::string rawJson;
			rawJson.assign(rawCommand.body, rawCommand.bodySize);

			Json::CharReaderBuilder builder;
			Json::CharReader* reader = builder.newCharReader();

			if (reader == nullptr)
				return nullptr;

			Json::Value root;
			reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.size(), &root, nullptr);
			command->Deserialize(root);

			delete reader;
			delete[] rawCommand.body;

			return command;
		}

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

		class DrawSpriteCommand final : public IJsonSerializable
		{
		public :

			DrawSpriteCommand(void) {}
			virtual ~DrawSpriteCommand(void) {}

			virtual void Serialize(Json::Value& root) override;
			virtual void Deserialize(Json::Value& root) override;
		};
	}

}
