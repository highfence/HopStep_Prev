#pragma once
#include "HSColor.h"
#include "../Extern/json/json.h"

namespace HopStep
{

	inline namespace Internal
	{
		enum class RenderCommandType : int
		{
			None,
			ClearScreen
		};

#pragma pack(push, 1)

		class RenderCommandHeader
		{
		public :

			RenderCommandType type = RenderCommandType::None;
			std::chrono::milliseconds tickTimeStamp;

			int bodySize = 0;
			char* body;
		};

#pragma pack(pop)

		__interface IJsonSerializable
		{
		public:
			virtual void Serialize(Json::Value& root) = 0;
			virtual void Deserialize(Json::Value& root) = 0;
		};

		class CJsonSerializer
		{
		public:
			static bool Serialize(IJsonSerializable* pObj, std::string& output);
			static bool Deserialize(IJsonSerializable* pObj, std::string& input);

		private:
			CJsonSerializer(void) {};
		};

		class ClearScreenCommand 
		{
		public :
			ClearScreenCommand(void) {}
			virtual ~ClearScreenCommand(void) {}

			HSColor m_ScreenColor;
		};
	}

}
