#include "stdafx.h"
#include "CppUnitTest.h"

#include "CoGBase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;



namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			Assert::AreEqual(2.9999999999999999, 3.0);
		}

		TEST_METHOD(Test_x_3x5_cog)
		{
			std::vector<double> num_of_pe_in_event_vec;
			num_of_pe_in_event_vec = {1, 2, 3, 4};
			
			MyClass m;
			//CoGBase cog_obj(num_of_pe_in_event_vec);

			Assert::AreEqual(2.9999999999999999, 3.0);
		}


	};
}