#include "stdafx.h"
#include "CppUnitTest.h"
#include "../HopStep/ByteSerialize.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HopStepUnitTest
{		
	TEST_CLASS(Serialize)
	{
	public:
		struct TestClass
		{
			int m_Int = 7;
			float m_Float = 0.5f;
			bool m_Bool = false;
			std::string m_String;
		};
		
		TEST_METHOD(SerializeTest)
		{

		}
	};
}