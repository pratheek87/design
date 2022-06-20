#include "pch.h"
#include "CppUnitTest.h"
#include "..\DesignPatterns\AbsFactory.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace myUnitTest
{
	TEST_CLASS(myUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			CWidgetFactory* pFactory = new CMacFactory();
			Assert::IsNotNull(pFactory);
		}
	};
}
