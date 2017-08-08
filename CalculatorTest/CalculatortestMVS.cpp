#include "stdafx.h"
#include "CppUnitTest.h"
#include "calculator.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTest//Unit test's in Microsoft Visual Studio
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_1plus2eq3)
		{
			Assert::AreEqual(3,calculator("1+2\n"),0.01);//1+2=3
		}
		TEST_METHOD(Test_3min1eq2)
		{
			Assert::AreEqual(2, calculator("3-1\n"),0.01);//3-1=2
		}
		TEST_METHOD(Test_3multipy1eq3)
		{
			Assert::AreEqual(3, calculator("3*1\n"), 0.01);//3*1=3
		}
		TEST_METHOD(Test_1divide2eq0p5)
		{
			Assert::AreEqual(0.5, calculator("1/2\n"), 0.01);//1/2=0.5
		}
		TEST_METHOD(Test_Brackets)
		{
			Assert::AreEqual(1, calculator("(1)\n"), 0);//(1)=1
		}
		TEST_METHOD(Test_BracketsNegative)
		{
			Assert::AreEqual(-1, calculator("(-1)\n"), 0);//(-1)=-1
		}
		TEST_METHOD(Test_Expression1)
		{
			Assert::AreEqual(1, calculator(" - 1 + 5 - 3\n"),0);//-1 + 5 - 3 = 1
		}
		TEST_METHOD(Test_Expression2)
		{
			Assert::AreEqual(8, calculator("-10 + (8 * 2.5) - (3 / 1, 5)\n"),0);//-10 + (8 * 2.5) - (3 / 1, 5) = 8
		}
		TEST_METHOD(Test_Expression3)
		{
			Assert::AreEqual(11, calculator("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)\n"), 0);//1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5) =11
		}
		
	};
}
