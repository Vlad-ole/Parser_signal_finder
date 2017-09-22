#include "stdafx.h"
#include "CppUnitTest.h"
//#include ""

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			Assert::AreEqual(2.0, 3.0);
		}

	};
}