#include "stdafx.h"
#include "CppUnitTest.h"
#include "../HopStep/HopStep.h"
#include "../HopStep/JsonSerialize.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepUnitTest
{		
	TEST_CLASS(Serialize)
	{
	public:
		struct TestClass : HopStep::IJsonSerializable
		{
			int m_Int = 7;
			float m_Float = 0.5f;
			bool m_Bool = false;
			std::string m_String;
			
			virtual void Serialize(Json::Value& root)
			{
				root["Int"] = m_Int;
				root["Float"] = m_Float;
				root["Bool"] = m_Bool;
			}
			virtual void Deserialize(Json::Value& root)
			{
				m_Int = root["Int"].asInt();
				m_Float = root["Float"].asFloat();
				m_Bool = root["Bool"].asBool();
			}
		};
		
		TEST_METHOD(SerializeTest)
		{
			//TestClass a;
			//a.m_String = "It is Test";

			//Json::Value root;
			//a.Serialize(root);
			//
			//TestClass b;
			//b.m_Int = 0;
			//b.m_Float = 0.0f;
			//b.m_Bool = true;
			//b.m_String.clear();

			//b.Deserialize(root);

			//Assert::AreEqual<int>(b.m_Int, a.m_Int);
			//Assert::AreEqual<float>(b.m_Float, a.m_Float);
			//Assert::AreEqual<bool>(b.m_Bool, a.m_Bool);
		}
	};
}