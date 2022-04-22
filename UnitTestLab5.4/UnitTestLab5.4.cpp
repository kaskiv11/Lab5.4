#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab5.4/Lab5.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab54
{
	TEST_CLASS(UnitTestLab54)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char g[6] = "g.dat";
			int t = phoneSearch(g, "3696898");
			Assert::AreEqual(t, -1);
		}
	};
}
