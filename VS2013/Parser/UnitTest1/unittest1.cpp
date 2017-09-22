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
		//TEST_METHOD(TestMethod2)
		//{
		//	Assert::AreEqual(2.999999999999999, 3.0);
		//}



		TEST_METHOD(Test_x_y_cog)
		{
			std::vector<double> num_of_pe_in_event_vec;
			num_of_pe_in_event_vec =
			{ 2, 7, 4, 9, 3, 4, 14, 11, 5, /*32-40*/
			4, 12, 6, 2, 0, 0, 0, 11, 10, 3, /*41-50*/
			5, 6, 9, 3, 8, 0, 20, 7, 4 };/*51-59*/
			
			CoGBase cog_obj(num_of_pe_in_event_vec);

			Assert::AreEqual(-0.693069307, cog_obj.GetX(), 0.0001);
			Assert::AreEqual(-0.925925926, cog_obj.GetY(), 0.0001);
		}


	};
}